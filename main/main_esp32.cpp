#include <string>

extern "C" {
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h" /**<logs: ESP_LOGI("TAG", "Info"); ESP_LOGW("TAG", "Warning"); ESP_LOGE("TAG", "Error");*/
}

#include "SPI.hpp"
#include "I2C.hpp"
#include "UART.hpp"

static const char* TAG = "PROTOCOL_DEMO";
const char* stateToString(az::Protocol::State state) {
    switch (state) {
        case az::Protocol::State::Ready: return "Ready";
        case az::Protocol::State::Uninitialized: return "Uninitialized";
        case az::Protocol::State::Error: return "Error";
        default: return "Unknown";
    }
}

extern "C" void app_main(void){
    std::string outdata;
     ESP_LOGI(TAG, "Logical protocols demo");

    az::UART uart_bad_conf(
        2,        /**<TX  */ 
        10,        /**< RX */ 
        20000,   /**<baudrate*/
        10,        /**< data bits - max 8 - wrong conf*/ 
        1         /**<stop bits*/ 
    );
    //UART - configuration
   ESP_LOGI(TAG, "UART state: %s", stateToString(uart_bad_conf.getState()));
   bool result = uart_bad_conf.setDataBits(6);
   ESP_LOGI(TAG, "UART: set Data Bits result: %d", result);
    result=uart_bad_conf.send("Hello ");
    ESP_LOGI(TAG, "UART: send result: %d", result);
    result=uart_bad_conf.receive(outdata);
    ESP_LOGI(TAG, "UART: recive result: %d", result);
    ESP_LOGI(TAG, "UART: received: %s", outdata.c_str());
    ESP_LOGI(TAG, "UART state: %s", stateToString(uart_bad_conf.getState()));
    result=uart_bad_conf.init();
    ESP_LOGI(TAG, "UART: init result: %d", result);
    ESP_LOGI(TAG, "UART state: %s", stateToString(uart_bad_conf.getState()));
    result=uart_bad_conf.setPinRx(2);
    ESP_LOGI(TAG, "UART: setPinRx(2) result: %d", result);
    ESP_LOGI(TAG,"UART: Pin Rx: %d",uart_bad_conf.getPinRx() );
    ESP_LOGI(TAG, "UART state: %s", stateToString(uart_bad_conf.getState()));
    //sending and recieving
    result=uart_bad_conf.send("Hello ");
    ESP_LOGI(TAG, "UART: send result: %d", result);
    result=uart_bad_conf.send("Kasia");
    ESP_LOGI(TAG, "UART: send result: %d", result);
    result=uart_bad_conf.receive(outdata);
    ESP_LOGI(TAG, "UART: recive result: %d", result);
    ESP_LOGI(TAG, "UART: received: %s", outdata.c_str());
    result=uart_bad_conf.deinit(); 
    ESP_LOGI(TAG, "UART: deinit result: %d", result);
    ESP_LOGI(TAG, "UART state: %s", stateToString(uart_bad_conf.getState()));

    //I2C - coniffiguration
    az::I2C i2c;
    ESP_LOGI(TAG, "I2C state: %s", stateToString(i2c.getState()));
    result=i2c.setSDApin(1);
    ESP_LOGI(TAG, "I2C: set SDA pin result: %d", result);
    result=i2c.setSCLpin(1);
    ESP_LOGI(TAG, "I2C: set SCL pin result: %d", result);
    result=i2c.setSCLpin(2);
    ESP_LOGI(TAG, "I2C: set SCL pin result: %d", result);
    result=i2c.setBusID(10);
    ESP_LOGI(TAG, "I2C: set  BUS ID result: %d", result);
    result=i2c.setDeviceAddress(12);
    ESP_LOGI(TAG, "I2C: set Device Addr result: %d", result);
    result=i2c.setFrequency(100000);
    ESP_LOGI(TAG, "I2C: set frequency result: %d", result);
     ESP_LOGI(TAG, "I2C state: %s", stateToString(i2c.getState()));
    result=i2c.init();
    ESP_LOGI(TAG, "I2C: init result: %d", result);
    ESP_LOGI(TAG, "I2C state: %s", stateToString(i2c.getState()));
    //sending and receiving
    result=i2c.send("\x31\x02\x05");
     ESP_LOGI(TAG, "I2C: send result: %d", result);
     result=i2c.receive(outdata);
    ESP_LOGI(TAG, "I2C: recive result: %d", result);
    ESP_LOGI(TAG, "I2C: recived: ");
    for(unsigned char c : outdata){
        ESP_LOGI(TAG, "0x%02X", c);
    }

    //SPI configuration
    az::SPI spi(1,2,3,4,10000, az::SPI::Mode::Mode1);
    ESP_LOGI(TAG,"SPI: MSB first?: %d",spi.getMSBfirst() );
    ESP_LOGI(TAG, "SPI state: %s", stateToString(spi.getState()));
    ESP_LOGI(TAG, "SPI mode: %d",static_cast<int>(spi.getMode()));
    //sending and receiving
    result=spi.send("\xD5\x05\xF5");
    ESP_LOGI(TAG, "SPI: send result: %d", result);
    result=spi.receive(outdata);
    ESP_LOGI(TAG, "SPI: recive result: %d", result);
    ESP_LOGI(TAG, "SPI received: ");
    for(unsigned char c:outdata){
        ESP_LOGI(TAG, "0x%02X", c);
    }
    result=spi.deinit();
    ESP_LOGI(TAG, "SPI: deinit result: %d", result);
    ESP_LOGI(TAG, "SPI state: %s", stateToString(spi.getState()));
    result=spi.send("\xD5\x05\xF5");
    ESP_LOGI(TAG, "SPI: send result: %d", result);


    while (true) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}