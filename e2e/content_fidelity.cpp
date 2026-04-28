// E2E test — CAL pub/sub content fidelity.
// Sets a known string on the outbound message and verifies the received copy
// carries the same value. The wire encoding is intentionally opaque here.

#include "uci/type/ActionCommandMT.h"
#include "uci/base/AbstractServiceBusConnection.h"
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

static const std::string kSentinel{"arcal-fidelity-sentinel"};

struct Listener : public uci::type::ActionCommandMT::Listener {
    std::string receivedSchemaVersion;
    void handleMessage(const uci::type::ActionCommandMT& msg) override {
        receivedSchemaVersion = msg.getMessageHeader().getSchemaVersion();
    }
};

int main() {
    auto* asb = uci_getAbstractServiceBusConnection("e2e_fidelity", "DDS");
    if (!asb) { std::cerr << "failed to get ASB\n"; return 1; }


    auto& reader = uci::type::ActionCommandMT::createReader("FidelityTopic", asb);
    auto& writer = uci::type::ActionCommandMT::createWriter("FidelityTopic", asb);

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    auto& msg = uci::type::ActionCommandMT::create(asb);
    msg.getMessageHeader().getSchemaVersion() = kSentinel;
    writer.write(msg);

    Listener listener;
    reader.read(2000, 1, listener);

    writer.close();
    uci::type::ActionCommandMT::destroy(msg);
    uci::type::ActionCommandMT::destroyWriter(writer);
    reader.close();
    uci::type::ActionCommandMT::destroyReader(reader);
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
