#pragma once
#include <boost/asio.hpp>
#include <memory>

using boost::asio::ip::tcp;

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
public:
    using pointer = std::shared_ptr<TcpConnection>;
private:
    tcp::socket _socket;
    std::string _message = "Hello from the server :D\n";

    explicit TcpConnection(boost::asio::io_context& ioContext);
public:
    // factory method 
    static pointer Create(boost::asio::io_context& ioContext) { return pointer(new TcpConnection(ioContext)); }
    // soocket getter
    tcp::socket& GetSocket() { return _socket; }
    // start the connection
    void Start();

};