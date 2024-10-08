#include <client/TcpClient.h>
#include <iostream>
#include <thread>

int main(int argc, char* argv[]) {
    Networking::TcpClient client {"localhost", 1337};

    client.OnMessage = [](const std::string& message) {
        std::cout << message;
    };

    // run client on a separate thread
    std::thread t{[&client] () { client.Run(); }};

    // on current thread run the input loop
    while(true) {
        std::string message;
        getline(std::cin, message);

        if (message == "\\q") break;
        message += "\n";

        client.Post(message);
    }

    // stop the client and wait for the thread
    client.Stop();
    t.join();
    return 0;
}