// Compile-only conformance: Listener / Reader / Writer / AbstractServiceBusConnectionStatusListener
// base class shapes.
//
// Spec: OMSC-SPC-008 RevK C++ CAL Spec, §§7300–7784
//
// CERTs covered:
//   CXX-010675  Listener class defined in uci::base namespace
//   CXX-010691  Listener dtor is virtual
//   CXX-010704  Listener default ctor is protected (disabled from public)
//   CXX-010717  Listener copy ctor is protected (disabled from public)
//   CXX-011182  Listener copy assignment is protected (disabled from public)
//   CXX-010733  Reader class defined in uci::base namespace
//   CXX-011094  Reader dtor is protected (disabled from public)
//   CXX-010763  Reader default ctor is protected
//   CXX-010776  Reader copy ctor is protected
//   CXX-011204  Reader copy assignment is protected
//   CXX-010792  Writer class defined in uci::base namespace
//   CXX-011095  Writer dtor is protected (disabled from public)
//   CXX-010822  Writer default ctor is protected
//   CXX-010835  Writer copy ctor is protected
//   CXX-011205  Writer copy assignment is protected
//   CXX-011324  AbstractServiceBusConnectionStatusListener in uci::base namespace
//   CXX-011341  AbstractServiceBusConnectionStatusListener dtor is virtual
//   CXX-011355  statusChanged(AbstractServiceBusConnectionStatusData) is pure virtual

#include "uci/base/Listener.h"
#include "uci/base/Reader.h"
#include "uci/base/Writer.h"
#include "uci/base/AbstractServiceBusConnectionStatusListener.h"

#include <type_traits>

namespace {

// ---------------------------------------------------------------------------
// CXX-010675: Listener defined in uci::base
// ---------------------------------------------------------------------------
static_assert(sizeof(uci::base::Listener) > 0,
    "CERT CXX-010675: uci::base::Listener must be defined");

// CXX-010691: Listener dtor must be virtual
static_assert(std::has_virtual_destructor_v<uci::base::Listener>,
    "CERT CXX-010691: ~uci::base::Listener() must be virtual");

// CXX-010704: Listener default ctor must be protected (not constructible from outside)
static_assert(!std::is_default_constructible_v<uci::base::Listener>,
    "CERT CXX-010704: uci::base::Listener default ctor must be protected");

// CXX-010717: Listener copy ctor must be protected (not copy-constructible from outside)
static_assert(!std::is_copy_constructible_v<uci::base::Listener>,
    "CERT CXX-010717: uci::base::Listener copy ctor must be protected");

// CXX-011182: Listener copy assignment must be protected (not copy-assignable from outside)
static_assert(!std::is_copy_assignable_v<uci::base::Listener>,
    "CERT CXX-011182: uci::base::Listener copy assignment must be protected");

// ---------------------------------------------------------------------------
// CXX-010733: Reader defined in uci::base
// ---------------------------------------------------------------------------
static_assert(sizeof(uci::base::Reader) > 0,
    "CERT CXX-010733: uci::base::Reader must be defined");

// CXX-011094: Reader dtor must be protected (not destructible from outside)
static_assert(!std::is_destructible_v<uci::base::Reader>,
    "CERT CXX-011094: ~uci::base::Reader() must be protected");

// CXX-010763: Reader default ctor must be protected
static_assert(!std::is_default_constructible_v<uci::base::Reader>,
    "CERT CXX-010763: uci::base::Reader default ctor must be protected");

// CXX-010776: Reader copy ctor must be protected
static_assert(!std::is_copy_constructible_v<uci::base::Reader>,
    "CERT CXX-010776: uci::base::Reader copy ctor must be protected");

// CXX-011204: Reader copy assignment must be protected
static_assert(!std::is_copy_assignable_v<uci::base::Reader>,
    "CERT CXX-011204: uci::base::Reader copy assignment must be protected");

// ---------------------------------------------------------------------------
// CXX-010792: Writer defined in uci::base
// ---------------------------------------------------------------------------
static_assert(sizeof(uci::base::Writer) > 0,
    "CERT CXX-010792: uci::base::Writer must be defined");

// CXX-011095: Writer dtor must be protected (not destructible from outside)
static_assert(!std::is_destructible_v<uci::base::Writer>,
    "CERT CXX-011095: ~uci::base::Writer() must be protected");

// CXX-010822: Writer default ctor must be protected
static_assert(!std::is_default_constructible_v<uci::base::Writer>,
    "CERT CXX-010822: uci::base::Writer default ctor must be protected");

// CXX-010835: Writer copy ctor must be protected
static_assert(!std::is_copy_constructible_v<uci::base::Writer>,
    "CERT CXX-010835: uci::base::Writer copy ctor must be protected");

// CXX-011205: Writer copy assignment must be protected
static_assert(!std::is_copy_assignable_v<uci::base::Writer>,
    "CERT CXX-011205: uci::base::Writer copy assignment must be protected");

// ---------------------------------------------------------------------------
// CXX-011324: AbstractServiceBusConnectionStatusListener defined in uci::base
// ---------------------------------------------------------------------------
static_assert(sizeof(uci::base::AbstractServiceBusConnectionStatusListener) > 0,
    "CERT CXX-011324: uci::base::AbstractServiceBusConnectionStatusListener must be defined");

// CXX-011341: AbstractServiceBusConnectionStatusListener dtor must be virtual
static_assert(
    std::has_virtual_destructor_v<uci::base::AbstractServiceBusConnectionStatusListener>,
    "CERT CXX-011341: ~uci::base::AbstractServiceBusConnectionStatusListener() must be virtual");

// CXX-011355: statusChanged must be pure virtual — verified by attempting to instantiate.
// A concrete subclass that implements statusChanged must compile; the abstract base must not.
static_assert(
    std::is_abstract_v<uci::base::AbstractServiceBusConnectionStatusListener>,
    "CERT CXX-011355: uci::base::AbstractServiceBusConnectionStatusListener must be abstract "
    "(statusChanged must be pure virtual)");

// Additionally verify the concrete override signature is accepted (proves the pure virtual
// method signature matches what the spec requires).
struct ConcreteStatusListener : public uci::base::AbstractServiceBusConnectionStatusListener {
    void statusChanged(
        uci::base::AbstractServiceBusConnectionStatusData /*newStatus*/) override {}
};

static_assert(!std::is_abstract_v<ConcreteStatusListener>,
    "CERT CXX-011355: ConcreteStatusListener must not be abstract after implementing statusChanged");

} // namespace
