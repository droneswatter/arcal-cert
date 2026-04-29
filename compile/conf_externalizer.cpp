// Compile-only conformance: uci::base::Externalizer and
// uci::base::ExternalizerLoader class shapes.
//
// Spec: OMSC-SPC-008 RevK C++ CAL Spec, Section "The Externalizer Class" and
//       Section "The ExternalizerLoader Class"
//       (lines 7785–8654 of 06_OMSC-SPC-008_RevK_CxxCALSpec_DandD_v2_5.md)
//
// CERTs covered — Externalizer:
//   CXX-012703 — destructor ~Externalizer() is protected (not publicly destructible)
//   CXX-012308 — default constructor Externalizer() is protected (not publicly default-constructible)
//   CXX-012321 — copy constructor Externalizer(const Externalizer&) is protected
//   CXX-012335 — operator=(const Externalizer&) is protected (not publicly copy-assignable)
//   CXX-012099 — public virtual void read(std::istream&, uci::base::Accessor&)
//   CXX-012115 — public virtual void read(const std::string&, uci::base::Accessor&)
//   CXX-012131 — public virtual void read(const std::vector<uint8_t>&, uci::base::Accessor&)
//   CXX-012146 — public virtual void write(const uci::base::Accessor&, std::ostream&)
//   CXX-012161 — public virtual void write(const uci::base::Accessor&, std::string&)
//   CXX-012176 — public virtual void write(const uci::base::Accessor&, std::vector<uint8_t>&)
//   CXX-012688 — public virtual bool messageReadOnly() const
//   CXX-012689 — public virtual bool messageWriteOnly() const
//   CXX-012690 — public virtual bool supportsObjectRead() const
//   CXX-012691 — public virtual bool supportsObjectWrite() const
//   CXX-012238 — public virtual std::string getCalApiVersion() const
//   CXX-012252 — public virtual std::string getEncoding() const
//   CXX-012266 — public virtual std::string getSchemaVersion() const
//   CXX-012280 — public virtual std::string getVendorVersion() const
//   CXX-012294 — public virtual std::string getVendor() const
//
// CERTs covered — ExternalizerLoader:
//   CXX-012338 — ExternalizerLoader class defined in namespace uci::base
//   CXX-012704 — destructor ~ExternalizerLoader() is protected (not publicly destructible)
//   CXX-012395 — default constructor ExternalizerLoader() is protected
//   CXX-012408 — copy constructor ExternalizerLoader(const ExternalizerLoader&) is protected
//   CXX-012422 — operator=(const ExternalizerLoader&) is protected
//   CXX-012367 — public non-static void getExternalizer(const std::string&, const std::string&, const std::string&)
//   CXX-012381 — public non-static void destroyExternalizer(uci::base::Externalizer*)
//   CXX-012434 — free function uci::base::ExternalizerLoader* uci_getExternalizerLoader() in global namespace
//   CXX-012446 — free function void uci_destroyExternalizerLoader(uci::base::ExternalizerLoader*) in global namespace
//
// Successful compilation IS the test. No runtime, no DDS required.

#include "uci/base/Externalizer.h"
#include "uci/base/ExternalizerLoader.h"

#include <cstdint>
#include <istream>
#include <ostream>
#include <string>
#include <type_traits>
#include <vector>

// ============================================================================
// Concrete subclasses used to verify the protected-member contract.
// They live in an anonymous namespace so they cannot be referenced externally.
// ============================================================================
namespace {

struct ConcreteExternalizer : public uci::base::Externalizer {
    void read(std::istream& is, uci::base::Accessor& t) override { (void)is; (void)t; }
    void read(const std::string& s, uci::base::Accessor& t) override { (void)s; (void)t; }
    void read(const std::vector<uint8_t>& v, uci::base::Accessor& t) override { (void)v; (void)t; }

    void write(const uci::base::Accessor& t, std::ostream& os) override { (void)t; (void)os; }
    void write(const uci::base::Accessor& t, std::string& s) override { (void)t; (void)s; }
    void write(const uci::base::Accessor& t, std::vector<uint8_t>& v) override { (void)t; (void)v; }

    bool messageReadOnly() const override { return false; }
    bool messageWriteOnly() const override { return false; }
    bool supportsObjectRead() const override { return true; }
    bool supportsObjectWrite() const override { return true; }

    std::string getCalApiVersion() const override { return {}; }
    std::string getEncoding() const override { return {}; }
    std::string getSchemaVersion() const override { return {}; }
    std::string getVendorVersion() const override { return {}; }
    std::string getVendor() const override { return {}; }
};

struct ConcreteExternalizerLoader : public uci::base::ExternalizerLoader {
    uci::base::Externalizer* getExternalizer(
        const std::string&, const std::string&, const std::string&) override {
        return nullptr;
    }
    void destroyExternalizer(uci::base::Externalizer* e) override { (void)e; }
};

// ============================================================================
// Externalizer — access-control checks
// ============================================================================

// CXX-012703: ~Externalizer() is protected — not publicly destructible.
static_assert(!std::is_destructible_v<uci::base::Externalizer>,
    "CXX-012703: ~Externalizer() must be protected, not public");

// CXX-012308: Externalizer() default ctor is protected — not publicly default-constructible.
static_assert(!std::is_default_constructible_v<uci::base::Externalizer>,
    "CXX-012308: Externalizer() must be protected, not public");

// CXX-012321: copy ctor is protected — not publicly copy-constructible.
static_assert(!std::is_copy_constructible_v<uci::base::Externalizer>,
    "CXX-012321: Externalizer(const Externalizer&) must be protected, not public");

// CXX-012335: copy assignment is protected — not publicly copy-assignable.
static_assert(!std::is_copy_assignable_v<uci::base::Externalizer>,
    "CXX-012335: operator=(const Externalizer&) must be protected, not public");

// Sanity: a subclass CAN be constructed (the protected members are accessible there).
static_assert(std::is_default_constructible_v<ConcreteExternalizer>,
    "Subclass of Externalizer must be default-constructible via the protected ctor");

// ============================================================================
// Externalizer — public virtual method signatures (CXX-012099 through CXX-012294)
// ============================================================================

// CXX-012099: virtual void read(std::istream&, uci::base::Accessor&)
using ReadIStreamFn = void (uci::base::Externalizer::*)(std::istream&, uci::base::Accessor&);
static_assert(std::is_same_v<
    decltype(static_cast<ReadIStreamFn>(&uci::base::Externalizer::read)),
    ReadIStreamFn>,
    "CXX-012099: virtual void read(std::istream&, Accessor&) must be public");

// CXX-012115: virtual void read(const std::string&, uci::base::Accessor&)
using ReadStringFn = void (uci::base::Externalizer::*)(const std::string&, uci::base::Accessor&);
static_assert(std::is_same_v<
    decltype(static_cast<ReadStringFn>(&uci::base::Externalizer::read)),
    ReadStringFn>,
    "CXX-012115: virtual void read(const std::string&, Accessor&) must be public");

// CXX-012131: virtual void read(const std::vector<uint8_t>&, uci::base::Accessor&)
using ReadVecFn = void (uci::base::Externalizer::*)(const std::vector<uint8_t>&, uci::base::Accessor&);
static_assert(std::is_same_v<
    decltype(static_cast<ReadVecFn>(&uci::base::Externalizer::read)),
    ReadVecFn>,
    "CXX-012131: virtual void read(const std::vector<uint8_t>&, Accessor&) must be public");

// CXX-012146: virtual void write(const uci::base::Accessor&, std::ostream&)
using WriteOStreamFn = void (uci::base::Externalizer::*)(const uci::base::Accessor&, std::ostream&);
static_assert(std::is_same_v<
    decltype(static_cast<WriteOStreamFn>(&uci::base::Externalizer::write)),
    WriteOStreamFn>,
    "CXX-012146: virtual void write(const Accessor&, std::ostream&) must be public");

// CXX-012161: virtual void write(const uci::base::Accessor&, std::string&)
using WriteStringFn = void (uci::base::Externalizer::*)(const uci::base::Accessor&, std::string&);
static_assert(std::is_same_v<
    decltype(static_cast<WriteStringFn>(&uci::base::Externalizer::write)),
    WriteStringFn>,
    "CXX-012161: virtual void write(const Accessor&, std::string&) must be public");

// CXX-012176: virtual void write(const uci::base::Accessor&, std::vector<uint8_t>&)
using WriteVecFn = void (uci::base::Externalizer::*)(const uci::base::Accessor&, std::vector<uint8_t>&);
static_assert(std::is_same_v<
    decltype(static_cast<WriteVecFn>(&uci::base::Externalizer::write)),
    WriteVecFn>,
    "CXX-012176: virtual void write(const Accessor&, std::vector<uint8_t>&) must be public");

// CXX-012688: virtual bool messageReadOnly() const
using MessageReadOnlyFn = bool (uci::base::Externalizer::*)() const;
static_assert(std::is_same_v<
    decltype(static_cast<MessageReadOnlyFn>(&uci::base::Externalizer::messageReadOnly)),
    MessageReadOnlyFn>,
    "CXX-012688: virtual bool messageReadOnly() const must be public");

// CXX-012689: virtual bool messageWriteOnly() const
using MessageWriteOnlyFn = bool (uci::base::Externalizer::*)() const;
static_assert(std::is_same_v<
    decltype(static_cast<MessageWriteOnlyFn>(&uci::base::Externalizer::messageWriteOnly)),
    MessageWriteOnlyFn>,
    "CXX-012689: virtual bool messageWriteOnly() const must be public");

// CXX-012690: virtual bool supportsObjectRead() const
using SupportsObjectReadFn = bool (uci::base::Externalizer::*)() const;
static_assert(std::is_same_v<
    decltype(static_cast<SupportsObjectReadFn>(&uci::base::Externalizer::supportsObjectRead)),
    SupportsObjectReadFn>,
    "CXX-012690: virtual bool supportsObjectRead() const must be public");

// CXX-012691: virtual bool supportsObjectWrite() const
using SupportsObjectWriteFn = bool (uci::base::Externalizer::*)() const;
static_assert(std::is_same_v<
    decltype(static_cast<SupportsObjectWriteFn>(&uci::base::Externalizer::supportsObjectWrite)),
    SupportsObjectWriteFn>,
    "CXX-012691: virtual bool supportsObjectWrite() const must be public");

// CXX-012238: virtual std::string getCalApiVersion() const
using GetCalApiVersionFn = std::string (uci::base::Externalizer::*)() const;
static_assert(std::is_same_v<
    decltype(static_cast<GetCalApiVersionFn>(&uci::base::Externalizer::getCalApiVersion)),
    GetCalApiVersionFn>,
    "CXX-012238: virtual std::string getCalApiVersion() const must be public");

// CXX-012252: virtual std::string getEncoding() const
using GetEncodingFn = std::string (uci::base::Externalizer::*)() const;
static_assert(std::is_same_v<
    decltype(static_cast<GetEncodingFn>(&uci::base::Externalizer::getEncoding)),
    GetEncodingFn>,
    "CXX-012252: virtual std::string getEncoding() const must be public");

// CXX-012266: virtual std::string getSchemaVersion() const
using GetSchemaVersionFn = std::string (uci::base::Externalizer::*)() const;
static_assert(std::is_same_v<
    decltype(static_cast<GetSchemaVersionFn>(&uci::base::Externalizer::getSchemaVersion)),
    GetSchemaVersionFn>,
    "CXX-012266: virtual std::string getSchemaVersion() const must be public");

// CXX-012280: virtual std::string getVendorVersion() const
using GetVendorVersionFn = std::string (uci::base::Externalizer::*)() const;
static_assert(std::is_same_v<
    decltype(static_cast<GetVendorVersionFn>(&uci::base::Externalizer::getVendorVersion)),
    GetVendorVersionFn>,
    "CXX-012280: virtual std::string getVendorVersion() const must be public");

// CXX-012294: virtual std::string getVendor() const
using GetVendorFn = std::string (uci::base::Externalizer::*)() const;
static_assert(std::is_same_v<
    decltype(static_cast<GetVendorFn>(&uci::base::Externalizer::getVendor)),
    GetVendorFn>,
    "CXX-012294: virtual std::string getVendor() const must be public");

// ============================================================================
// ExternalizerLoader — namespace check (CXX-012338)
// ============================================================================

// CXX-012338: ExternalizerLoader is defined in namespace uci::base.
static_assert(std::is_class_v<uci::base::ExternalizerLoader>,
    "CXX-012338: uci::base::ExternalizerLoader must be a class in namespace uci::base");

// ============================================================================
// ExternalizerLoader — access-control checks
// ============================================================================

// CXX-012704: ~ExternalizerLoader() is protected — not publicly destructible.
static_assert(!std::is_destructible_v<uci::base::ExternalizerLoader>,
    "CXX-012704: ~ExternalizerLoader() must be protected, not public");

// CXX-012395: ExternalizerLoader() default ctor is protected.
static_assert(!std::is_default_constructible_v<uci::base::ExternalizerLoader>,
    "CXX-012395: ExternalizerLoader() must be protected, not public");

// CXX-012408: copy ctor is protected.
static_assert(!std::is_copy_constructible_v<uci::base::ExternalizerLoader>,
    "CXX-012408: ExternalizerLoader(const ExternalizerLoader&) must be protected, not public");

// CXX-012422: copy assignment is protected.
static_assert(!std::is_copy_assignable_v<uci::base::ExternalizerLoader>,
    "CXX-012422: operator=(const ExternalizerLoader&) must be protected, not public");

// Sanity: a subclass CAN be constructed.
static_assert(std::is_default_constructible_v<ConcreteExternalizerLoader>,
    "Subclass of ExternalizerLoader must be default-constructible via the protected ctor");

// ============================================================================
// ExternalizerLoader — public member function signatures
// ============================================================================

// CXX-012367: uci::base::Externalizer* getExternalizer(const std::string&,
//             const std::string&, const std::string&)
using GetExternalizerFn =
    uci::base::Externalizer* (uci::base::ExternalizerLoader::*)(
        const std::string&, const std::string&, const std::string&);
static_assert(std::is_same_v<
    decltype(static_cast<GetExternalizerFn>(&uci::base::ExternalizerLoader::getExternalizer)),
    GetExternalizerFn>,
    "CXX-012367: getExternalizer(const std::string&, const std::string&, const std::string&) "
    "must be a public non-static member function returning Externalizer*");

// CXX-012381: void destroyExternalizer(uci::base::Externalizer*)
using DestroyExternalizerFn =
    void (uci::base::ExternalizerLoader::*)(uci::base::Externalizer*);
static_assert(std::is_same_v<
    decltype(static_cast<DestroyExternalizerFn>(&uci::base::ExternalizerLoader::destroyExternalizer)),
    DestroyExternalizerFn>,
    "CXX-012381: destroyExternalizer(Externalizer*) must be a public non-static member function");

// ============================================================================
// Global-namespace free functions (CXX-012434, CXX-012446)
// ============================================================================

// CXX-012434: uci::base::ExternalizerLoader* uci_getExternalizerLoader() in global namespace.
static_assert(std::is_same_v<
    decltype(&::uci_getExternalizerLoader),
    uci::base::ExternalizerLoader* (*)()>,
    "CXX-012434: uci_getExternalizerLoader() must be a free function in the global namespace "
    "returning uci::base::ExternalizerLoader*");

// CXX-012446: void uci_destroyExternalizerLoader(uci::base::ExternalizerLoader*) in global namespace.
static_assert(std::is_same_v<
    decltype(&::uci_destroyExternalizerLoader),
    void (*)(uci::base::ExternalizerLoader*)>,
    "CXX-012446: uci_destroyExternalizerLoader(ExternalizerLoader*) must be a free function "
    "in the global namespace");

} // anonymous namespace
