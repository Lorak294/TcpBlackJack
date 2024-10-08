#include "server/TcpServer.h"
#include <iostream>

namespace Networking {

    using boost::asio::ip::tcp;

    // ======================== Private methods ========================
    void TcpServer::startAccepting() {
        // create new socket where new connection will be awaited
        _socket.emplace(_ioContext);

        // async accept new connection
        _acceptor.async_accept(*_socket,
            [this](const boost::system::error_code& error){

                // create new connection (move socket obj into the connection)
                auto connection = TcpConnection::Create(std::move(*_socket));
                _connections.insert(connection);

                if(OnJoin) {
                    OnJoin(connection);
                }

                // start the connection
                if(!error) {
                    connection->Start(
                        [this](const std::string& msg) { if(OnClientMessage) OnClientMessage(msg);},
                        [&, weak = std::weak_ptr(connection)]() {
                            if(auto shared = weak.lock(); shared && _connections.erase(shared)) {
                                if(OnLeave){
                                    OnLeave(shared);
                                }
                            }
                        }
                    );
                }
                
                // recursively wait for another connection 
                startAccepting();
        });
    }

    // ======================== Public methods ========================
    TcpServer::TcpServer(Ipv ipv, int port) : 
        _ipVersion(ipv), 
        _port(port), 
        _acceptor(tcp::acceptor(_ioContext, tcp::endpoint(_ipVersion == Ipv::V4 ? tcp::v4() : tcp::v6(),_port))) {}

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
