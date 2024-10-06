#pragma once

#include <boost/asio.hpp>
#include <server/TcpConnection.h>
#include <functional>
#include <optional>
#include <unordered_set>
#include <string>

namespace Networking {
    namespace io = boost::asio;

    enum class Ipv {
        V4,
        V6
    };
    
    class TcpServer
    {
    private:
        Ipv _ipVersion;
        int _port;

        io::io_context _ioContext;
        io::ip::tcp::acceptor _acceptor;

        // dummmy socket for accepting new connections
        std::optional<io::ip::tcp::socket> _socket;
        
        // set of current connections
        std::unordered_set<TcpConnection::pointer> _connections {};

        void startAccepting();

    public:
        TcpServer(Ipv ipv, int port);

        int Run();
        void Broadcast(const std::string& message);
    };
}
