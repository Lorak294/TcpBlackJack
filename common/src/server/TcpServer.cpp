#include "server/TcpServer.h"
#include <iostream>

namespace Networking {

    using boost::asio::ip::tcp;

    TcpServer::TcpServer(Ipv ipv, int port) : 
        _ipVersion(ipv), 
        _port(port), 
        _acceptor(tcp::acceptor(_ioContext, tcp::endpoint(_ipVersion == Ipv::V4 ? tcp::v4() : tcp::v6(),_port))) {}


    void TcpServer::startAccepting() {
        // create new socket where new connection will be awaited
        _socket.emplace(_ioContext);

        // async accept new connection
        _acceptor.async_accept(*_socket,
            [this](const boost::system::error_code& error){

                // create new connection (move socket obj into the connection)
                auto connection = TcpConnection::Create(std::move(*_socket));
                _connections.insert(connection);

                // start the connection
                if(!error) {
                    connection->Start();
                }
                
                // recursively wait for another connection 
                startAccepting();
        });
    }

    int TcpServer::Run() {
        try
        {
            startAccepting();
            _ioContext.run();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return -1;
        }
        return 0;
    }

    void TcpServer::Broadcast(const std::string& message) {
        for(auto& connection : _connections) {
            connection->Post(message);
        }
    }
}
