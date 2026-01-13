cmake_minimum_required(VERSION 3.16)
project(protocols_desktop LANGUAGES CXX)

add_library(protocols STATIC
    ../components/protocols/src/Protocol.cpp
    ../components/protocols/src/UART.cpp
    ../components/protocols/src/I2C.cpp
    ../components/protocols/src/SPI.cpp
)

target_include_directories(protocols PUBLIC
    ../components/protocols/include
)

add_executable(protocols_desktop
    main_desktop.cpp
)

target_link_libraries(protocols_desktop protocols)