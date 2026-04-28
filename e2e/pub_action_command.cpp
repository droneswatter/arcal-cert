// E2E smoke test — publisher side.
// Publishes one ServiceStatusMT on the "ServiceStatus" topic and exits 0.
// Intended to run ~1 second after the subscriber starts so DDS peer discovery
// has completed.  Run via run_e2e_action_command.sh or manually:
//
//   ./e2e_sub &; sleep 1; ./e2e_pub

#include "uci/type/ServiceStatusMT.h"
#include "uci/base/AbstractServiceBusConnection.h"
#include <chrono>
#include <iostream>
#include <thread>

int main() {
    auto* asb = uci_getAbstractServiceBusConnection("e2e_pub", "DDS");
    if (!asb) { std::cerr << "pub: failed to get ASB\n"; return 1; }


    auto& writer = uci::type::ServiceStatusMT::createWriter("ServiceStatus", asb);

    // Wait for DDS peer discovery (SPDP) before writing.
    // With BestEffort QoS, messages sent before discovery completes are lost.
    // Loopback unicast discovery completes in <10ms; 300ms is generous margin.
    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    auto& msg = uci::type::ServiceStatusMT::create(asb);
    writer.write(msg);

    // Give DDS time to deliver before tearing down the participant.
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    writer.close();
    uci::type::ServiceStatusMT::destroy(msg);
    uci::type::ServiceStatusMT::destroyWriter(writer);

    asb->shutdown();
    uci_destroyAbstractServiceBusConnection(asb);

    std::cout << "pub: sent one ServiceStatusMT\n";
    return 0;
}
