#include <iostream>
#include <string>

#include "SPI.hpp"
#include "I2C.hpp"
#include "UART.hpp"

const char* stateToString(az::Protocol::State state) {
    switch (state) {
        case az::Protocol::State::Ready:         return "Ready";
        case az::Protocol::State::Uninitialized: return "Uninitialized";
        case az::Protocol::State::Error:         return "Error";
        default:                                 return "Unknown";
    }
}

int main() {
    std::string outdata;

    std::cout << "Logical protocols demo\n";
    //UART
    az::UART uart_bad_conf(
         2,        /**<TX  */ 
        10,        /**< RX */ 
        20000,   /**<baudrate*/
        10,        /**< data bits - max 8 - wrong conf*/ 
        1         /**<stop bits*/ 
    );
    //configuration
    std::cout << "UART state: " << stateToString(uart_bad_conf.getState()) << "\n";
    bool result = uart_bad_conf.setDataBits(6);
    std::cout << "UART: set Data Bits result: " << result << "\n";
    result = uart_bad_conf.send("Hello ");
    std::cout << "UART: send result: " << result << "\n";
    result = uart_bad_conf.receive(outdata);
    std::cout << "UART: receiv result: " << result << "\n";
    std::cout << "UART: received: " << outdata << "\n";
    result = uart_bad_conf.init();
    std::cout << "UART: init result: " << result << "\n";
    std::cout << "UART state: " << stateToString(uart_bad_conf.getState()) << "\n";
    result = uart_bad_conf.setPinRx(2);
    std::cout << "UART: setPinRx(2) result : " << result << "\n";
    std::cout << "UART: Pin Rx : " << uart_bad_conf.getPinRx() << "\n";
    //sending and recieving:
    result = uart_bad_conf.send("Hello ");
    result = uart_bad_conf.send("Kasia");
    result = uart_bad_conf.receive(outdata);
    std::cout << "UART: received: " << outdata << "\n";
    //deinit
    result = uart_bad_conf.deinit();
    std::cout << "UART: deinit result: " << result << "\n";
    std::cout << "UART state: " << stateToString(uart_bad_conf.getState()) << "\n";

    //I2C:
    az::I2C i2c;
    std::cout << "I2C state: " << stateToString(i2c.getState()) << "\n";
    //configuration
    i2c.setSDApin(1);
    i2c.setSCLpin(2);
    i2c.setBusID(10);
    i2c.setDeviceAddress(12);
    i2c.setFrequency(100000);

    result = i2c.init();
    std::cout << "I2C: init result: " << result << "\n";
    //sending and recieving
    result = i2c.send("\x31\x02\x05");
    std::cout << "I2C: send result: " << result << "\n";
    result = i2c.receive(outdata);
    std::cout << "I2C: receive result: " << result << "\n";
    std::cout << "I2C received bytes:\n";

    for (unsigned char c : outdata) {
        std::cout << "0x" << std::hex << static_cast<int>(c) << std::dec << "\n";
    }

    std::cout << "\n";

    //SPI configuration
    az::SPI spi(1, 2, 3, 4, 10000, az::SPI::Mode::Mode1);
    std::cout << "SPI MSB first: " << spi.getMSBfirst() << "\n";
    std::cout << "SPI state: " << stateToString(spi.getState()) << "\n";
    std::cout << "SPI mode: " << static_cast<int>(spi.getMode()) << "\n";
    //sending and reciving
    result = spi.send("\xD5\x05\xF5");
    std::cout << "SPI: send result: " << result << "\n";
    result = spi.receive(outdata);
    std::cout << "SPI: receive result: " << result << "\n";
    std::cout << "SPI received bytes:\n";
    for (unsigned char c : outdata) {
        std::cout << "0x" << std::hex << static_cast<int>(c) << std::dec << "\n";
    }

    result = spi.deinit();
    std::cout << "SPI: deinit result: " << result << "\n";
    std::cout << "SPI state: " << stateToString(spi.getState()) << "\n";

    return 0;
}
