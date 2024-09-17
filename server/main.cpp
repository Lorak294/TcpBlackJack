#include <iostream>
#include "Card.h"
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(){

    try {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(),7000));
    }
    catch(std::exception& e)
    {

    }

    std::cout << "Hello server" << std::endl;

    Card c1 = Card('K','A');
    Card c2 = Card('T','A');
    Card c3 = Card('6','A');
    std::cout << c1.ToString() << '\t' << c1.GetValue() << std::endl;
    std::cout << c2.ToString() << '\t' << c2.GetValue() << std::endl;
    std::cout << c2.ToString() << '\t' << c3.GetValue() << std::endl;
    
    return 0;
}