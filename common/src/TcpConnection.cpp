#include "TcpConnection.h"
#include <iostream>

using boost::asio::ip::tcp;

TcpConnection::TcpConnection(boost::asio::io_context& ioContext): _socket(tcp::socket(ioContext)){
}

// TcpConnection::~TcpConnection(){

// }

void TcpConnection::Start() {

    auto strongThis = shared_from_this();
    boost::asio::async_write(_socket,boost::asio::buffer(_message),
        [strongThis](const boost::system::error_code& error, size_t bytesTransfered){
            if(error){
                std::cerr << "Failed to send message!\n";
            } else {
                std::cout << "Sent " << bytesTransfered << " bytes of data.\n";
            }
    });

    boost::asio::streambuf buffer;
    _socket.async_receive(buffer.prepare(512),[this](const boost::system::error_code& error, size_t bytesTransfered){
        if(error == boost::asio::error::eof){
            std::cout << "Client terminated the connection\n";
        } else if(error) {
            std::cerr << "Client disconected unproperly!\n";
            //throw boost::system::system_error(error);
        }
    });
}