// E2E test — reader/writer close lifecycle.
// Verifies that read/write operations after close report errors through the
// public CAL API.

#include "uci/base/AbstractServiceBusConnection.h"
#include "uci/type/ServiceStatusMT.h"

#include <cassert>
#include <exception>
#include <iostream>

struct Listener : public uci::type::ServiceStatusMT::Listener {
    void handleMessage(const uci::type::ServiceStatusMT&) override {}
};

template <typename Fn>
bool throwsException(Fn&& fn) {
    try {
        fn();
    } catch (const std::exception&) {
        return true;
    }
    return false;
}

int main() {
    auto* asb = uci_getAbstractServiceBusConnection("e2e_close", "DDS");
    if (!asb) { std::cerr << "failed to get ASB\n"; return 1; }

    auto& reader = uci::type::ServiceStatusMT::createReader("CloseLifecycleTopic", asb);
    auto& writer = uci::type::ServiceStatusMT::createWriter("CloseLifecycleTopic", asb);

    reader.close();
    writer.close();

    Listener listener;
    auto& msg = uci::type::ServiceStatusMT::create(asb);

    const bool readThrows = throwsException([&] {
        reader.read(10, 1, listener);
    });
    const bool readNoWaitThrows = throwsException([&] {
        reader.readNoWait(1, listener);
    });
    const bool writeThrows = throwsException([&] {
        writer.write(msg);
    });

    uci::type::ServiceStatusMT::destroy(msg);
    uci::type::ServiceStatusMT::destroyReader(reader);
    uci::type::ServiceStatusMT::destroyWriter(writer);
    asb->shutdown();
    uci_destroyAbstractServiceBusConnection(asb);

    assert(readThrows && "read after close must throw");
    assert(readNoWaitThrows && "readNoWait after close must throw");
    assert(writeThrows && "write after close must throw");

    std::cout << "PASS reader_writer_close\n";
    return 0;
}
