// E2E test — multiple messages delivered in full.
// Publishes N messages and verifies the reader receives exactly N.

#include "uci/type/ServiceStatusMT.h"
#include "uci/base/AbstractServiceBusConnection.h"
#include <chrono>
#include <iostream>
#include <thread>

static constexpr int kN = 5;

struct Listener : public uci::type::ServiceStatusMT::Listener {
    int received{0};
    void handleMessage(const uci::type::ServiceStatusMT&) override { ++received; }
};

int main() {
    auto* asb = uci_getAbstractServiceBusConnection("e2e_multi", "DDS");
    if (!asb) { std::cerr << "failed to get ASB\n"; return 1; }


    auto& reader = uci::type::ServiceStatusMT::createReader("MultiTopic", asb);
    auto& writer = uci::type::ServiceStatusMT::createWriter("MultiTopic", asb);

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    // Write and read one at a time: default QoS is KeepLast(1), so rapid-fire
    // writes would overwrite the buffer before they are read.
    Listener listener;
    auto& msg = uci::type::ServiceStatusMT::create(asb);
    for (int i = 0; i < kN; ++i) {
        writer.write(msg);
        reader.read(2000, 1, listener);
    }

    writer.close();
    uci::type::ServiceStatusMT::destroy(msg);
    uci::type::ServiceStatusMT::destroyWriter(writer);
    reader.close();
    uci::type::ServiceStatusMT::destroyReader(reader);
    asb->shutdown();
    uci_destroyAbstractServiceBusConnection(asb);

    if (listener.received == kN) {
        std::cout << "received " << listener.received << "/" << kN << " — PASS\n";
        return 0;
    }
    std::cerr << "received " << listener.received << "/" << kN << " — FAIL\n";
    return 1;
}
