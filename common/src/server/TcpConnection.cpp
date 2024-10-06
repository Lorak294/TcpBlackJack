#include "server/TcpConnection.h"
#include <iostream>

namespace Networking {

    TcpConnection::TcpConnection(io::ip::tcp::socket&& socket): _socket(std::move(socket)) {
        boost::system::error_code ec;
        // set the username as remote address
        std::stringstream name;
        name << _socket.remote_endpoint();
        _username = name.str();
    }
    
    // awaits for a new message from client
    void TcpConnection::asyncRead(){
        io::async_read_until(_socket,_streambuff,"\n",[self = shared_from_this()](boost::system::error_code ec, size_t bytesTransfered){
            self->onRead(ec,bytesTransfered);
        });
    }
    void TcpConnection::onRead(boost::system::error_code& ec, size_t bytesTransfered) {
        if(ec) {
            _socket.close(ec);

            // TODO: add error handler
            return;
        }

        // read the message from the buffer
        std::stringstream message;
        message << _username << ": " << std::istream(&_streambuff).rdbuf();
        _streambuff.consume(bytesTransfered);

        std::cout << message.str();

        // TODO: add message handler

        // recursively call next reading 
        asyncRead();
    }
    
    // awaits for a new message to be sent to client
    void TcpConnection::asyncWrite() {
        io::async_write(_socket,io::buffer(_outgoingMessages.front()),[self = shared_from_this()](boost::system::error_code ec, size_t bytesTransfered){
            self->onWrite(ec,bytesTransfered);
        });
    }
    void TcpConnection::onWrite(boost::system::error_code& ec, size_t bytesTransfered){
        if(ec) {
            _socket.close(ec);

            // TODO: add error handler
            return;
        }

        // remove message that was sent from the queue
        _outgoingMessages.pop();

        // if there are other messages to be sent, write again
        if(!_outgoingMessages.empty()){
            asyncWrite();
        }

    }

    void TcpConnection::Start() {
        asyncRead();
    }

    // sends message to the client 
    void TcpConnection::Post(const std::string& message) {
        bool isQueueIdle = _outgoingMessages.empty();

        _outgoingMessages.push(message);
        // if messages are not already beeing set start sending
        if(isQueueIdle) {
            asyncWrite();
        }
    }
}
