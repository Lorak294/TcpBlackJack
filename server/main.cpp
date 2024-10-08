#include <iostream>
#include <server/TcpServer.h>

int main(int argc, char* argv[]){

    Networking::TcpServer server(Networking::Ipv::V4,1337);
    
    server.OnJoin = [](Networking::TcpConnection::pointer conn) {
        std::cout << "User " << conn->GetUsername() << " has joined the server" << std::endl;
    };
    server.OnLeave = [](Networking::TcpConnection::pointer conn) {
        std::cout << "User " << conn->GetUsername() << " has left the server" << std::endl;
    };
    server.OnClientMessage = [&server](const std::string& msg) {
        // TODO: parse msg
        // TODO: update game state
        server.Broadcast(msg);
    };

    server.Run();
    
    return 0;
}