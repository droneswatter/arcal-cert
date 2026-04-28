// E2E test — CAL pub/sub content fidelity.
// Sets a known string on the outbound message and verifies the received copy
// carries the same value. The wire encoding is intentionally opaque here.

#include "uci/type/ServiceStatusMT.h"
#include "uci/base/AbstractServiceBusConnection.h"
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

static const std::string kSentinel{"arcal-fidelity-sentinel"};

struct Listener : public uci::type::ServiceStatusMT::Listener {
    std::string receivedSchemaVersion;
    void handleMessage(const uci::type::ServiceStatusMT& msg) override {
        receivedSchemaVersion = msg.getMessageHeader().getSchemaVersion();
    }
};

int main() {
    auto* asb = uci_getAbstractServiceBusConnection("e2e_fidelity", "DDS");
    if (!asb) { std::cerr << "failed to get ASB\n"; return 1; }


    auto& reader = uci::type::ServiceStatusMT::createReader("FidelityTopic", asb);
    auto& writer = uci::type::ServiceStatusMT::createWriter("FidelityTopic", asb);

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    auto& msg = uci::type::ServiceStatusMT::create(asb);
    msg.getMessageHeader().getSchemaVersion() = kSentinel;
    writer.write(msg);

    Listener listener;
    reader.read(2000, 1, listener);

    writer.close();
    uci::type::ServiceStatusMT::destroy(msg);
    uci::type::ServiceStatusMT::destroyWriter(writer);
    reader.close();
    uci::type::ServiceStatusMT::destroyReader(reader);
    asb->shutdown();
    uci_destroyAbstractServiceBusConnection(asb);

    if (listener.receivedSchemaVersion == kSentinel) {
        std::cout << "SchemaVersion='" << listener.receivedSchemaVersion << "' — PASS\n";
        return 0;
    }
    std::cerr << "got '" << listener.receivedSchemaVersion
              << "' expected '" << kSentinel << "' — FAIL\n";
    return 1;
}
