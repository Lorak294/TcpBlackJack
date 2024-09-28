#include <iostream>
#include "Card.h"
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[]){

    try
    {
        boost::asio::io_context io_context;
        // resolve the enpoint which will be listend
        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1","1337");

        // connect endpoint to a socket
        tcp::socket socket(io_context);
        boost::asio::connect(socket,endpoints);

        // listen to messages in a loop
        while(true) {
            std::array<char,128> buffer;
            boost::system::error_code error;

            // read the message into the buffer
            size_t length = socket.read_some(boost::asio::buffer(buffer),error);
            
            // if we receive eof the server has closed the connection
            if(error == boost::asio::error::eof) {
                break;
            } else if(error){
                throw boost::system::system_error(error);
            }

            // print the message
            std::cout.write(buffer.data(),length);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}