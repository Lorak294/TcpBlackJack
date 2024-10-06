#include <iostream>
#include "Card.h"
#include <boost/asio.hpp>
#include <TcpServer.h>

using boost::asio::ip::tcp;

int main(int argc, char* argv[]){

    TcpServer server(tcp::v4(),1337);
    server.Run();
    
    return 0;
}