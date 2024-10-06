#pragma once
#include <string>
#include <boost/asio.hpp>
#include <TcpConnection.h>

class TcpServer
{
private:
    boost::asio::ip::tcp _ipVersion;
    int _port;

    boost::asio::io_context _ioContext;
    boost::asio::ip::tcp::acceptor _acceptor;
    std::vector<TcpConnection::pointer> _connections {};

    void startAccepting();

public:
    TcpServer(boost::asio::ip::tcp ipv, int port);
    //~TcpListener();

    int Run();
};
