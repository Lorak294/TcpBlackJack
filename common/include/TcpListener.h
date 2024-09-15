#pragma once
#include <string>

class TcpListener
{
private:
    const std::string   ip_address; // IP address listener will run on
    int                 port;       // port for the web sevice
    int                 socket;     // fd for listening socket

public:
    TcpListener(const std::string ip_address, int port) : ip_address(ip_address), port(port) {}
    //~TcpListener();

    int Init();
    int Run();
};
