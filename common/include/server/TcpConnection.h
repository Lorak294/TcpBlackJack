#pragma once

#include <boost/asio.hpp>
#include <memory>
#include <queue>

namespace Networking {
    using boost::asio::ip::tcp;
    namespace io = boost::asio;

    using MessageHandler = std::function<void(std::string)>;
    using ErrorHandler = std::function<void()>;

    class TcpConnection : public std::enable_shared_from_this<TcpConnection>
    {
    public:
        using pointer = std::shared_ptr<TcpConnection>;
    private:
        // bound socket
        tcp::socket _socket;
        // client username
        std::string _username;
        // queue of messages awaiting to be sent
        std::queue<std::string> _outgoingMessages;
        // buffer for storing incoming messages
        io::streambuf _streambuff = io::streambuf(65536);
    
        // handlers
        MessageHandler _messageHandler;
        ErrorHandler _errorHandler;
        
    private:    
        // private constructor
        explicit TcpConnection(io::ip::tcp::socket&& socket);

        // awaits for a new message from client
        void asyncRead();
        void onRead(boost::system::error_code& ec, size_t bytesTransfered);
        // awaits for a new message to be sent to client
        void asyncWrite();
        void onWrite(boost::system::error_code& ec, size_t bytesTransfered);
    
    public:
        // factory method that receives rvalue socket
        static pointer Create(io::ip::tcp::socket&& socket) { return pointer(new TcpConnection(std::move(socket))); }
        
        // username getter
        inline const std::string& GetUsername() { return _username; }
        // socket getter
        tcp::socket& GetSocket() { return _socket; }
        
        // starts the connection
        void Start(MessageHandler&& messageHandler, ErrorHandler&& errorHandler);

        // sends message to the client
        void Post(const std::string& message);

    };
}
