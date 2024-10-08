#include <client/TcpClient.h>
#include <iostream>

namespace Networking {

    TcpClient::TcpClient(const std::string& address, int port) : _socket(_ioContext) {
        io::ip::tcp::resolver resolver {_ioContext};
        _endpoints = resolver.resolve(address, std::to_string(port));
    }

    void TcpClient::Run() {
        io::async_connect(_socket, _endpoints, [this](boost::system::error_code ec, io::ip::tcp::endpoint ep) {
            if (!ec)
                asyncRead();
        });

        _ioContext.run();
    }

    void TcpClient::Stop() {
        boost::system::error_code ec;
        _socket.close(ec);

        if (ec) {
            // process error
        }
    }

    void TcpClient::Post(const std::string &message) {
        bool queueIdle = _outgoingMessages.empty();
        _outgoingMessages.push(message);

        if (queueIdle) {
            asyncWrite();
        }
    }

    void TcpClient::asyncRead() {
        io::async_read_until(_socket, _streambuff, "\n", [this](boost::system::error_code ec, size_t bytesTransferred) {
           onRead(ec, bytesTransferred);
        });
    }

    void TcpClient::onRead(boost::system::error_code ec, size_t bytesTransferred) {
        if (ec) {
            Stop();
            return;
        }

        std::stringstream message;
        message << std::istream{&_streambuff}.rdbuf();
        OnMessage(message.str());
        asyncRead();
    }

    void TcpClient::asyncWrite() {
        io::async_write(_socket, io::buffer(_outgoingMessages.front()), [this](boost::system::error_code ec, size_t bytesTransferred) {
            onWrite(ec, bytesTransferred);
        });
    }

    void TcpClient::onWrite(boost::system::error_code ec, size_t bytesTransferred) {
        if (ec) {
            Stop();
            return;
        }

        _outgoingMessages.pop();

        if (!_outgoingMessages.empty()) {
            asyncWrite();
        }
    }
}