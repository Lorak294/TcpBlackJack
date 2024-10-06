#pragma once
#include <string>
#include <boost/asio.hpp>
#include <server/TcpConnection.h>
#include <functional>

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

    template<typename T>
    void WriteToClient(int connectionIdx, const T& message);


    // callback takes the connection index and incoming message of type T
    template<typename T>
    using ListenCallback = std::function<void(int,const T&)>;
    template<typename T>
    void RegisterListenCallback(ListenCallback<T> callback);
};
