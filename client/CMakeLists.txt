cmake_minimum_required(VERSION 3.20.0)
set(CMAKE_CXX_STANDARD 20)

project(client)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} 
    PUBLIC 
        common
)
target_link_libraries(${PROJECT_NAME} 
    PUBLIC 
        common
)