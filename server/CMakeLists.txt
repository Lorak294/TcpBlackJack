add_executable(server main.cpp)
target_link_libraries(server PUBLIC common)

target_include_directories(server PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(server PUBLIC ${Boost_LIBRARIES})