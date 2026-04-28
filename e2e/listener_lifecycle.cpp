// E2E test — addListener / removeListener lifecycle.
// Verifies that a removed listener stops receiving messages.

#include "uci/type/ServiceStatusMT.h"
#include "uci/base/AbstractServiceBusConnection.h"
#include <chrono>
#include <iostream>
#include <thread>

struct Listener : public uci::type::ServiceStatusMT::Listener {
    int received{0};
    void handleMessage(const uci::type::ServiceStatusMT&) override { ++received; }
};

int main() {
    auto* asb = uci_getAbstractServiceBusConnection("e2e_listener", "DDS");
    if (!asb) { std::cerr << "failed to get ASB\n"; return 1; }


    auto& reader = uci::type::ServiceStatusMT::createReader("ListenerTopic", asb);
    auto& writer = uci::type::ServiceStatusMT::createWriter("ListenerTopic", asb);

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    Listener listener;
    reader.addListener(listener);

    // Publish and wait for background delivery.
    auto& msg = uci::type::ServiceStatusMT::create(asb);
    writer.write(msg);
    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    int afterFirst = listener.received;

    reader.removeListener(listener);

    // Publish again — removed listener must not receive this.
    writer.write(msg);
    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    int afterSecond = listener.received;

    writer.close();
    uci::type::ServiceStatusMT::destroy(msg);
    uci::type::ServiceStatusMT::destroyWriter(writer);
    reader.close();
    uci::type::ServiceStatusMT::destroyReader(reader);
    asb->shutdown();
    uci_destroyAbstractServiceBusConnection(asb);

    if (afterFirst == 1 && afterSecond == 1) {
        std::cout << "after-add=" << afterFirst << " after-remove=" << afterSecond << " — PASS\n";
        return 0;
    }
    std::cerr << "after-add=" << afterFirst << " after-remove=" << afterSecond
              << " (expected 1 and 1) — FAIL\n";
    return 1;
}
