add_executable(client main.cpp)
target_link_libraries(client PUBLIC common)

target_include_directories(client PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(client PUBLIC ${Boost_LIBRARIES})