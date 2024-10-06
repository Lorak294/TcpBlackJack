file(GLOB SOURCES src/*.cpp)
add_library(common STATIC ${SOURCES})

target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(common PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(common PUBLIC ${Boost_LIBRARIES})