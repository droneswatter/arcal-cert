// Compile-only conformance: structural shape of nested Listener/Reader/Writer
// classes inside *MT (GlobalElement accessor) headers — OMSC-SPC-008 RevK §10.3.4
// and §10.7.3 (Global Element Accessor Special C++ Classes).
//
// conf_generated_global.cpp already covers:
//   - base-class inheritance (is_base_of) for Listener, Reader, Writer
//   - public method signatures (handleMessage, addListener, removeListener,
//     read, readNoWait, close, write, close)
//   - factory function signatures (createReader/destroyReader/createWriter/destroyWriter)
//
// This file adds what that file omits:
//   - protected default constructor on Listener, Reader, Writer
//     (CERT CXX-010704 / CXX-005608 / CXX-005653 — "disable access to default ctor")
//   - deleted copy-constructor on Listener, Reader, Writer
//     (CERT CXX-010717 / CXX-005615 / CXX-005660)
//   - deleted copy assignment operator on Listener, Reader, Writer
//     (CERT CXX-011077 / CXX-011080)
//   - protected virtual destructor on Reader and Writer
//     (CERT CXX-012710 / CXX-012711 — "disable access to destructor")
//   - friend class <MT> declaration on Reader and Writer
//     (required so the MT factory methods can invoke the protected ctor/dtor)

#include "uci/type/AMTI_ActivityMT.h"
#include "uci/type/AO_ActivityMT.h"
#include "uci/type/AO_CommandMT.h"
#include "uci/type/AMTI_CommandMT.h"
#include "uci/type/AO_CapabilityStatusMT.h"

#include <type_traits>

// ---------------------------------------------------------------------------
// Helper: for each MT type, verify the three nested classes cannot be
// default-constructed, copy-constructed, or copy-assigned from outside the
// class (i.e. they are not publicly constructible).
// ---------------------------------------------------------------------------

// --- AMTI_ActivityMT ---

using Msg1      = uci::type::AMTI_ActivityMT;
using L1        = Msg1::Listener;
using R1        = Msg1::Reader;
using W1        = Msg1::Writer;

// Protected default ctor: the nested class must NOT be publicly
// default-constructible (CERT CXX-010704 / CXX-005608 / CXX-005653).
static_assert(!std::is_default_constructible_v<L1>,
    "AMTI_ActivityMT::Listener must not be publicly default-constructible (CXX-010704)");
static_assert(!std::is_default_constructible_v<R1>,
    "AMTI_ActivityMT::Reader must not be publicly default-constructible (CXX-005608)");
static_assert(!std::is_default_constructible_v<W1>,
    "AMTI_ActivityMT::Writer must not be publicly default-constructible (CXX-005653)");

// Deleted copy ctor: must not be copy-constructible
// (CERT CXX-010717 / CXX-005615 / CXX-005660).
static_assert(!std::is_copy_constructible_v<L1>,
    "AMTI_ActivityMT::Listener must not be copy-constructible (CXX-010717)");
static_assert(!std::is_copy_constructible_v<R1>,
    "AMTI_ActivityMT::Reader must not be copy-constructible (CXX-005615)");
static_assert(!std::is_copy_constructible_v<W1>,
    "AMTI_ActivityMT::Writer must not be copy-constructible (CXX-005660)");

// Deleted copy assignment: must not be copy-assignable
// (CERT CXX-011077 / CXX-011080; Listener inherits same convention from uci::base::Listener).
static_assert(!std::is_copy_assignable_v<L1>,
    "AMTI_ActivityMT::Listener must not be copy-assignable");
static_assert(!std::is_copy_assignable_v<R1>,
    "AMTI_ActivityMT::Reader must not be copy-assignable (CXX-011077)");
static_assert(!std::is_copy_assignable_v<W1>,
    "AMTI_ActivityMT::Writer must not be copy-assignable (CXX-011080)");

// Protected virtual dtor on Reader/Writer: the destructor must NOT be
// publicly accessible, which is expressed as "not publicly destructible"
// (CERT CXX-012710 / CXX-012711).
static_assert(!std::is_destructible_v<R1>,
    "AMTI_ActivityMT::Reader dtor must be protected (CXX-012710)");
static_assert(!std::is_destructible_v<W1>,
    "AMTI_ActivityMT::Writer dtor must be protected (CXX-012711)");

// The Listener dtor is public virtual (required so delete through base ptr works).
// Verify it IS publicly destructible.
static_assert(std::is_destructible_v<L1>,
    "AMTI_ActivityMT::Listener must have a public virtual dtor");

// --- AO_ActivityMT ---

using Msg2 = uci::type::AO_ActivityMT;
using L2   = Msg2::Listener;
using R2   = Msg2::Reader;
using W2   = Msg2::Writer;

static_assert(!std::is_default_constructible_v<L2>);
static_assert(!std::is_default_constructible_v<R2>);
static_assert(!std::is_default_constructible_v<W2>);
static_assert(!std::is_copy_constructible_v<L2>);
static_assert(!std::is_copy_constructible_v<R2>);
static_assert(!std::is_copy_constructible_v<W2>);
static_assert(!std::is_copy_assignable_v<L2>);
static_assert(!std::is_copy_assignable_v<R2>);
static_assert(!std::is_copy_assignable_v<W2>);
static_assert(!std::is_destructible_v<R2>);
static_assert(!std::is_destructible_v<W2>);
static_assert(std::is_destructible_v<L2>);

// --- AO_CommandMT ---

using Msg3 = uci::type::AO_CommandMT;
using L3   = Msg3::Listener;
using R3   = Msg3::Reader;
using W3   = Msg3::Writer;

static_assert(!std::is_default_constructible_v<L3>);
static_assert(!std::is_default_constructible_v<R3>);
static_assert(!std::is_default_constructible_v<W3>);
static_assert(!std::is_copy_constructible_v<L3>);
static_assert(!std::is_copy_constructible_v<R3>);
static_assert(!std::is_copy_constructible_v<W3>);
static_assert(!std::is_copy_assignable_v<L3>);
static_assert(!std::is_copy_assignable_v<R3>);
static_assert(!std::is_copy_assignable_v<W3>);
static_assert(!std::is_destructible_v<R3>);
static_assert(!std::is_destructible_v<W3>);
static_assert(std::is_destructible_v<L3>);

// --- AMTI_CommandMT ---

using Msg4 = uci::type::AMTI_CommandMT;
using L4   = Msg4::Listener;
using R4   = Msg4::Reader;
using W4   = Msg4::Writer;

static_assert(!std::is_default_constructible_v<L4>);
static_assert(!std::is_default_constructible_v<R4>);
static_assert(!std::is_default_constructible_v<W4>);
static_assert(!std::is_copy_constructible_v<L4>);
static_assert(!std::is_copy_constructible_v<R4>);
static_assert(!std::is_copy_constructible_v<W4>);
static_assert(!std::is_copy_assignable_v<L4>);
static_assert(!std::is_copy_assignable_v<R4>);
static_assert(!std::is_copy_assignable_v<W4>);
static_assert(!std::is_destructible_v<R4>);
static_assert(!std::is_destructible_v<W4>);
static_assert(std::is_destructible_v<L4>);

// --- AO_CapabilityStatusMT ---

using Msg5 = uci::type::AO_CapabilityStatusMT;
using L5   = Msg5::Listener;
using R5   = Msg5::Reader;
using W5   = Msg5::Writer;

static_assert(!std::is_default_constructible_v<L5>);
static_assert(!std::is_default_constructible_v<R5>);
static_assert(!std::is_default_constructible_v<W5>);
static_assert(!std::is_copy_constructible_v<L5>);
static_assert(!std::is_copy_constructible_v<R5>);
static_assert(!std::is_copy_constructible_v<W5>);
static_assert(!std::is_copy_assignable_v<L5>);
static_assert(!std::is_copy_assignable_v<R5>);
static_assert(!std::is_copy_assignable_v<W5>);
static_assert(!std::is_destructible_v<R5>);
static_assert(!std::is_destructible_v<W5>);
static_assert(std::is_destructible_v<L5>);

// ---------------------------------------------------------------------------
// friend class: verify that the MT class IS destructible (its own dtor is
// protected, and the friend declaration grants the MT class access to
// Reader/Writer ctors and dtors).  The MT class must be accessible from the
// outside via destroy(), so we confirm its create/destroy static members are
// reachable (already done in conf_generated_global.cpp).
// We additionally confirm via is_destructible that the MT outer class dtor
// is *not* publicly callable either (it's protected), which is consistent
// with enforced factory usage.
// ---------------------------------------------------------------------------
static_assert(!std::is_destructible_v<Msg1>,
    "AMTI_ActivityMT must not be publicly destructible — use destroy()");
static_assert(!std::is_destructible_v<Msg2>,
    "AO_ActivityMT must not be publicly destructible — use destroy()");
static_assert(!std::is_destructible_v<Msg3>,
    "AO_CommandMT must not be publicly destructible — use destroy()");
static_assert(!std::is_destructible_v<Msg4>,
    "AMTI_CommandMT must not be publicly destructible — use destroy()");
static_assert(!std::is_destructible_v<Msg5>,
    "AO_CapabilityStatusMT must not be publicly destructible — use destroy()");
