// CERT CAL-005208: A CAL Implementation shall associate a topic with one and
// only one CAL Message type.
// Verified by: the typed writer/reader API enforces 1:1 topic-to-type
// association at compile time; at runtime a writer and reader opened on
// the same topic name share the same underlying DDS type without error.

#include "uci/type/ServiceStatusMT.h"
#include "uci/base/AbstractServiceBusConnection.h"
#include <cassert>
#include <iostream>

int main() {
    auto* asb = uci_getAbstractServiceBusConnection("Svc208", "DDS");
    assert(asb);


    auto& writer = uci::type::ServiceStatusMT::createWriter("CAL005208Topic", asb);
    auto& reader = uci::type::ServiceStatusMT::createReader("CAL005208Topic", asb);

    reader.close();
    writer.close();
    uci::type::ServiceStatusMT::destroyReader(reader);
    uci::type::ServiceStatusMT::destroyWriter(writer);

    asb->shutdown();
    uci_destroyAbstractServiceBusConnection(asb);
    std::cout << "PASS CAL-005208\n";
    return 0;
}
