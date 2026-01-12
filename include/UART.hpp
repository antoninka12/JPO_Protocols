#pragma once
#include "Protocol.hpp"

namespace az{

    class UART : public Protocol{
        private:
            int m_pinTx;
            int m_pinRx;
            int m_baudRate;
            int m_dataBits;
            int m_stopBits;
            bool m_parity; //1:even, 0:odd enum mozna zrobic
            void initHardware();
            void deinitHardware();
            bool isConfigValid() const;
        public:
            //default constructor
            UART();
            //parametrized constructor
            UART(int pinTx, int pinRx, int baudRate, int dataBits, int stopBits);
            UART(int pinTx, int pinRx, int baudRate, int dataBits, int stopBits, bool parity);
            //destructor
            ~UART() override;
            bool send(const std::string& data) override;
            bool receive(std::string& outData) override;
            bool init();
            bool deinit();

            //setters and getters
            bool setPinTx(int pinTx);
            int getPinTx() const;

            bool setPinRx(int pinRx);
            int getPinRx() const;

            bool setBaudRate(int baudRate);
            int getBaudRate() const;

            bool setDataBits(int dataBits);
            int getDataBits() const;

            bool setStopBits(int stopBits);
            int getStopBits() const;

            bool setParity(bool parity);
            bool getParity() const;

    };
}//namespace az