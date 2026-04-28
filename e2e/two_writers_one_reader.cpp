// E2E test — two writers, one reader.
// Verifies that a reader receives messages from two independent writers
// on the same topic.

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
    auto* asb = uci_getAbstractServiceBusConnection("e2e_2w1r", "DDS");
    if (!asb) { std::cerr << "failed to get ASB\n"; return 1; }


    auto& reader   = uci::type::ServiceStatusMT::createReader("SharedTopic", asb);
    auto& writerA  = uci::type::ServiceStatusMT::createWriter("SharedTopic", asb);
    auto& writerB  = uci::type::ServiceStatusMT::createWriter("SharedTopic", asb);

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    // Write and read one at a time: default QoS is KeepLast(1), so sending
    // from both writers without reading would leave only the latest sample.
    Listener listener;
    auto& msg = uci::type::ServiceStatusMT::create(asb);
    writerA.write(msg);
    reader.read(2000, 1, listener);
    writerB.write(msg);
    reader.read(2000, 1, listener);

    writerA.close();
    uci::type::ServiceStatusMT::destroy(msg);
    uci::type::ServiceStatusMT::destroyWriter(writerA);
    writerB.close();
    uci::type::ServiceStatusMT::destroyWriter(writerB);
    reader.close();
    uci::type::ServiceStatusMT::destroyReader(reader);
    asb->shutdown();
    uci_destroyAbstractServiceBusConnection(asb);

    if (listener.received == 2) {
        std::cout << "received " << listener.received << "/2 — PASS\n";
        return 0;
    }
    std::cerr << "received " << listener.received << "/2 — FAIL\n";
    return 1;
}
