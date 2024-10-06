#include "server/TcpServer.h"
#include <iostream>

using boost::asio::ip::tcp;

TcpServer::TcpServer(tcp ipv, int port) : 
    _ipVersion(ipv), 
    _port(port), 
    _acceptor(tcp::acceptor(_ioContext, tcp::endpoint(ipv,_port))) {}


void TcpServer::startAccepting() {
    // create connection
    auto connection = TcpConnection::Create(_ioContext);
    _connections.push_back(connection);

    // async accept new connection
    _acceptor.async_accept(connection->GetSocket(),
        [connection, this](const boost::system::error_code& error){
            if(!error) {
                connection->Start();
            }

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