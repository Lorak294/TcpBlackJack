#pragma once

#include <boost/asio.hpp>
#include <functional>
#include <queue>

namespace Networking {
    namespace io = boost::asio;
    using MessageHandler = std::function<void(std::string)>;

    class TcpClient {
    private:
        io::io_context _ioContext {};
        io::ip::tcp::socket _socket;
        io::ip::tcp::resolver::results_type _endpoints;
        
        io::streambuf _streambuff = io::streambuf(65536);
        std::queue<std::string> _outgoingMessages {};
    
    public:
        MessageHandler OnMessage;
    
    private:
        void asyncRead();
        void onRead(boost::system::error_code ec, size_t bytesTransfered);
        void asyncWrite();
        void onWrite(boost::system::error_code ec, size_t bytesTransfered);

    public:
        TcpClient(const std::string& address, int port);

        void Run();
        void Stop();
        void Post(const std::string& msg);
    };
    
}   