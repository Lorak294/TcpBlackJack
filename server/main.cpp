#include <iostream>
#include "Card.h"
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[]){
    try
    {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context,tcp::endpoint(tcp::v4(),1337));

        while(true) {
            std::cout << "listening for a new connection...\n";
            // create socket
            tcp::socket socket(io_context);

            // await and accept connection on a socket
            acceptor.accept(socket);
            std::cout << "new connection accepted!\n";
            // write messeage to connected client
            std::string hello_msg = "Hello from the server :D\n";
            boost::system::error_code error;
            boost::asio::write(socket,boost::asio::buffer(hello_msg),error);

            // here socket goes out of scope and closes
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
    return 0;
}