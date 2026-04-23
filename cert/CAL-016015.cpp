// CERT CAL-016015: A CAL Implementation shall provide multiple CAL Clients
// operating in a single address space with the same behavior as if each CAL
// Client were executing in separate address spaces. Specifically: each receives
// a distinct Service UUID, and pub/sub between them works correctly.

#include "uci/base/AbstractServiceBusConnection.h"
#include "uci/type/ActionCommandMT.h"
#include <cassert>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

struct Listener : public uci::type::ActionCommandMT::Listener {
    std::string schemaVersion;
    void handleMessage(const uci::type::ActionCommandMT& msg) override {
        schemaVersion = msg.getMessageHeader().getSchemaVersion().getValue();
    }
};

int main() {
    auto* asb1 = uci_getAbstractServiceBusConnection("ServiceA", "DDS");
    auto* asb2 = uci_getAbstractServiceBusConnection("ServiceB", "DDS");

    assert(asb1 != nullptr);
    assert(asb2 != nullptr);

    auto uuid1 = asb1->getMyServiceUUID();
    auto uuid2 = asb2->getMyServiceUUID();

    assert(uuid1 != uuid2 && "Two distinct service labels must produce distinct Service UUIDs");

    auto& reader = uci::type::ActionCommandMT::createReader("CAL016015Topic", asb2);
    auto& writer = uci::type::ActionCommandMT::createWriter("CAL016015Topic", asb1);

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    const std::string sentinel = "cal-016015";
    uci::type::ActionCommandMT msg;
    msg.getMessageHeader().getSchemaVersion().setValue(sentinel);
    writer.write(msg);

    Listener listener;
    reader.read(2000, 1, listener);
    assert(listener.schemaVersion == sentinel
           && "multiple CAL clients in one process must exchange messages");

    writer.close();
    reader.close();
    uci::type::ActionCommandMT::destroyWriter(writer);
    uci::type::ActionCommandMT::destroyReader(reader);

    asb1->shutdown();
    asb2->shutdown();
    uci_destroyAbstractServiceBusConnection(asb1);
    uci_destroyAbstractServiceBusConnection(asb2);

    std::cout << "PASS CAL-016015\n";
    return 0;
}
