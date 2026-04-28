// E2E test — two readers, one writer.
// Verifies that each reader independently receives a copy of every published
// message on the same topic.

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
    auto* asb = uci_getAbstractServiceBusConnection("e2e_1w2r", "DDS");
    if (!asb) { std::cerr << "failed to get ASB\n"; return 1; }


    auto& readerA = uci::type::ServiceStatusMT::createReader("BroadcastTopic", asb);
    auto& readerB = uci::type::ServiceStatusMT::createReader("BroadcastTopic", asb);
    auto& writer  = uci::type::ServiceStatusMT::createWriter("BroadcastTopic", asb);

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    auto& msg = uci::type::ServiceStatusMT::create(asb);
    writer.write(msg);

    Listener listenerA, listenerB;
    readerA.read(2000, 1, listenerA);
    readerB.read(2000, 1, listenerB);

    writer.close();
    uci::type::ServiceStatusMT::destroy(msg);
    uci::type::ServiceStatusMT::destroyWriter(writer);
    readerA.close();
    uci::type::ServiceStatusMT::destroyReader(readerA);
    readerB.close();
    uci::type::ServiceStatusMT::destroyReader(readerB);
    asb->shutdown();
    uci_destroyAbstractServiceBusConnection(asb);

    if (listenerA.received == 1 && listenerB.received == 1) {
        std::cout << "readerA=" << listenerA.received
                  << " readerB=" << listenerB.received << " — PASS\n";
        return 0;
    }
    std::cerr << "readerA=" << listenerA.received
              << " readerB=" << listenerB.received
              << " (expected 1 and 1) — FAIL\n";
    return 1;
}
