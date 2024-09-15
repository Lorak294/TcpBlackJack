cmake_minimum_required(VERSION 3.20.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(tcpblackjack)

add_subdirectory(common)
add_subdirectory(server)
add_subdirectory(client)

