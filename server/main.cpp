#include <iostream>
#include <server/TcpServer.h>

int main(int argc, char* argv[]){

    Networking::TcpServer serv(Networking::Ipv::V4,1337);
    serv.Run();
    
    return 0;
}