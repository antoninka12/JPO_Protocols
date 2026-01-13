cmake_minimum_required(VERSION 3.16)
project(protocols_desktop)

add_subdirectory(../components/protocols protocols)

add_executable(protocols_demo main.cpp)

target_include_directories(protocols_demo PRIVATE
    ../components/protocols/include
)

target_link_libraries(protocols_demo protocols)