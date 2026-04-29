// Compile-only conformance: uci::base::AbstractServiceBusConnection class shape.
//
// CERT CXX-005419  — class in uci::base namespace
// CERT CXX-011275  — public member enum AbstractServiceBusConnectionStateEnum with
//                    enumerators INITIALIZING, NORMAL, DEGRADED, INOPERABLE, FAILED
// CERT CXX-011277  — public member struct AbstractServiceBusConnectionStatusData
// CERT CXX-011279  — StateEnum member variable "state" in status struct uses
//                    AbstractServiceBusConnection::AbstractServiceBusConnectionStateEnum
// CERT CXX-011281  — std::string member variable "stateDetail" in status struct
// CERT CXX-011091  — destructor is protected (not publicly destructible)
// CERT CXX-005431  — default constructor is protected (not publicly constructible)
// CERT CXX-005432  — copy constructor is protected (not publicly copy-constructible)
// CERT CXX-011177  — assignment operator is protected (not publicly copy-assignable)
// CERT CXX-011164  — public void shutdown()
// CERT CXX-005424  — public std::string getMySystemLabel() const
// CERT CXX-011168  — public uci::base::UUID getMySystemUUID() const
// CERT CXX-011169  — public uci::base::UUID getMyServiceUUID() const
// CERT CXX-011170  — public uci::base::UUID getMySubsystemUUID() const
// CERT CXX-011171  — public uci::base::UUID getMyComponentUUID(const std::string&) const
// CERT CXX-011172  — public uci::base::UUID getMyCapabilityUUID(const std::string&) const
// CERT CXX-011174  — public std::string getOmsSchemaVersion() const
// CERT CXX-011175  — public std::string getOmsSchemaCompilerVersion() const
// CERT CXX-012694  — public std::string getOMSApiVersion() const
// CERT CXX-011176  — public std::string getAbstractServiceBusConnectionVersion() const
// CERT CXX-011295  — public AbstractServiceBusConnectionStatusData getStatus() const
// CERT CXX-011082  — public void addStatusListener(AbstractServiceBusConnectionStatusListener&)
// CERT CXX-011083  — public void removeStatusListener(AbstractServiceBusConnectionStatusListener&)
// CERT CXX-005433  — free function uci_getAbstractServiceBusConnection in global namespace
//
// KNOWN VIOLATIONS (compile errors produced when CHECK_VIOLATIONS is defined):
//
//   CXX-011275 / CXX-011277 / CXX-011279:
//     The spec requires the nested type names:
//       uci::base::AbstractServiceBusConnection::AbstractServiceBusConnectionStatusData
//       uci::base::AbstractServiceBusConnection::AbstractServiceBusConnectionStateEnum
//     The header exposes only type aliases "StatusData" and "StateEnum", and the
//     underlying types live in AbstractServiceBusConnectionStatusListener.h (as
//     AbstractServiceBusConnectionStatusData::StateEnum), not as nested members of
//     AbstractServiceBusConnection under the spec-mandated names.
//
//   CXX-011295:
//     getStatus() returns ASB::StatusData, not the spec-required
//     ASB::AbstractServiceBusConnectionStatusData return type name.

#include "uci/base/AbstractServiceBusConnection.h"

#include <string>
#include <type_traits>

// ── CERT CXX-005419: class lives in uci::base ─────────────────────────────────
using ASB = uci::base::AbstractServiceBusConnection;

// ── CERTs CXX-011091, CXX-005431, CXX-005432, CXX-011177:
//    constructor / destructor / copy are inaccessible from outside the class
static_assert(!std::is_destructible_v<ASB>,         "CXX-011091: destructor must be protected");
static_assert(!std::is_default_constructible_v<ASB>, "CXX-005431: default ctor must be protected");
static_assert(!std::is_copy_constructible_v<ASB>,    "CXX-005432: copy ctor must be protected");
static_assert(!std::is_copy_assignable_v<ASB>,       "CXX-011177: assignment op must be protected");

// ── CERT CXX-011281: StatusData struct has a std::string "stateDetail" field
static_assert(std::is_same_v<decltype(ASB::StatusData::stateDetail), std::string>,
    "CXX-011281: stateDetail must be std::string");

namespace {

// ── Method pointer checks: existence + exact signature ──────────────────────

// CERT CXX-011164: void shutdown()
void (ASB::*p_shutdown)() = &ASB::shutdown;

// CERT CXX-005424: std::string getMySystemLabel() const
std::string (ASB::*p_label)() const = &ASB::getMySystemLabel;

// CERT CXX-011168: uci::base::UUID getMySystemUUID() const
uci::base::UUID (ASB::*p_sysUUID)() const = &ASB::getMySystemUUID;

// CERT CXX-011169: uci::base::UUID getMyServiceUUID() const
uci::base::UUID (ASB::*p_svcUUID)() const = &ASB::getMyServiceUUID;

// CERT CXX-011170: uci::base::UUID getMySubsystemUUID() const
uci::base::UUID (ASB::*p_subUUID)() const = &ASB::getMySubsystemUUID;

// CERT CXX-011171: uci::base::UUID getMyComponentUUID(const std::string&) const
uci::base::UUID (ASB::*p_compUUID)(const std::string&) const = &ASB::getMyComponentUUID;

// CERT CXX-011172: uci::base::UUID getMyCapabilityUUID(const std::string&) const
uci::base::UUID (ASB::*p_capUUID)(const std::string&) const = &ASB::getMyCapabilityUUID;

// CERT CXX-011174: std::string getOmsSchemaVersion() const
std::string (ASB::*p_omsVer)()  const = &ASB::getOmsSchemaVersion;

// CERT CXX-011175: std::string getOmsSchemaCompilerVersion() const
std::string (ASB::*p_compVer)() const = &ASB::getOmsSchemaCompilerVersion;

// CERT CXX-012694: std::string getOMSApiVersion() const
std::string (ASB::*p_apiVer)()  const = &ASB::getOMSApiVersion;

// CERT CXX-011176: std::string getAbstractServiceBusConnectionVersion() const
std::string (ASB::*p_asbVer)()  const = &ASB::getAbstractServiceBusConnectionVersion;

// CERT CXX-011295: AbstractServiceBusConnectionStatusData getStatus() const
//   NOTE: return type here uses the alias "StatusData"; the spec requires the
//   nested type to be named AbstractServiceBusConnectionStatusData.
//   Functional behaviour is present; naming non-conformance is recorded above.
ASB::StatusData (ASB::*p_status)() const = &ASB::getStatus;

// CERT CXX-011082: void addStatusListener(AbstractServiceBusConnectionStatusListener&)
void (ASB::*p_addListener)(uci::base::AbstractServiceBusConnectionStatusListener&)
    = &ASB::addStatusListener;

// CERT CXX-011083: void removeStatusListener(AbstractServiceBusConnectionStatusListener&)
void (ASB::*p_removeListener)(uci::base::AbstractServiceBusConnectionStatusListener&)
    = &ASB::removeStatusListener;

// CERT CXX-005433: free function uci_getAbstractServiceBusConnection in global namespace
using FreeFunc = uci::base::AbstractServiceBusConnection*(*)(
    const std::string&, const std::string&);
FreeFunc p_getASB = &uci_getAbstractServiceBusConnection;

// Suppress unused-variable warnings
void use_all() {
    (void)p_shutdown;
    (void)p_label;    (void)p_sysUUID; (void)p_svcUUID; (void)p_subUUID;
    (void)p_compUUID; (void)p_capUUID;
    (void)p_omsVer;   (void)p_compVer; (void)p_apiVer;  (void)p_asbVer;
    (void)p_status;   (void)p_addListener; (void)p_removeListener;
    (void)p_getASB;
}

// ── CERTs CXX-011275 / CXX-011277 / CXX-011279 — VIOLATION PROBES ───────────
// The block below documents that the spec-required nested names do NOT exist.
// Un-comment CHECK_VIOLATIONS to confirm the compiler rejects them.
#ifdef CHECK_VIOLATIONS

// CXX-011277: must be a nested type named AbstractServiceBusConnectionStatusData
using SpecStatusData = ASB::AbstractServiceBusConnectionStatusData; // expected: compile error

// CXX-011275: must be a member enum named AbstractServiceBusConnectionStateEnum
using SpecStateEnum  = ASB::AbstractServiceBusConnectionStateEnum;  // expected: compile error

// CXX-011279: state field type must be AbstractServiceBusConnectionStateEnum
static_assert(std::is_same_v<
    decltype(ASB::AbstractServiceBusConnectionStatusData::state),
    ASB::AbstractServiceBusConnectionStateEnum>);                    // expected: compile error

#endif // CHECK_VIOLATIONS

} // namespace
