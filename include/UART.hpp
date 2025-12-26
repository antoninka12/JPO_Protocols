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
            bool m_parity; //1:even, 0:odd
            void initHardware(){
                setState(State::Ready);
            }
            void deinitHardware(){
                setState(State::Uninitialized);
            }
            bool isConfigValid() const{
                return m_pinTx>=0 && 
                m_pinRx>=0 && 
                m_baudRate>0 &&
                m_dataBits>=5 && 
                m_dataBits<=8 && 
                m_stopBits>=1 &&
                m_stopBits<=2;
            }
            public:
            //default constructor
            UART():Protocol("UART", Type::UART),m_pinTx(-1), m_pinRx(-1), m_baudRate(0), m_dataBits(0), m_stopBits(0), m_parity(-1){}
            //parametrized constructor
            UART(int pinTx, int pinRx, int baudRate, int dataBits, int stopBits):Protocol("UART", Type::UART),m_pinTx(pinTx), m_pinRx(pinRx), m_baudRate(baudRate), 
            m_dataBits(dataBits), m_stopBits(stopBits){
                if(!isConfigValid){
                    setState(State::Error);
                    return;
                }
                initHardware();
            }
            UART(int pinTx, int pinRx, int baudRate, int dataBits, int stopBits, bool parity):Protocol("UART", Type::UART),m_pinTx(pinTx), m_pinRx(pinRx), m_baudRate(baudRate), 
            m_dataBits(dataBits), m_stopBits(stopBits), m_parity(parity){
                if(!isConfigValid){
                    setState(State::Error);
                    return;
                }
                initHardware();
            }
            //destructor
            ~UART() override {
                if(getState()==State::Ready){
                    deinitHardware();
                }
            }
            bool send(const std::string& data) override{

            }
            bool receive(std::string& outdata) override{

            }

            //setters and getters
            void setPinTx(int pinTx){
                if(pinTx>=0&& pinTx!=m_pinRx){
                    m_pinTx=pinTx;
                }
                setState(State::Uninitialized);
            }
            int getPintX() const{
                return m_pinTx;
            }
            void setPinRx(int pinRx){
                if(pinRx>=0 && pinRx!=m_pinTx){
                    m_pinRx=pinRx;
                }
                setState(State::Uninitialized);
            }
            int getPinRx() const{
                return m_pinRx;
            }
            void setBaudRate(int baudRate){
                if(baudRate>0){
                    m_baudRate=baudRate;
                }
                setState(State::Uninitialized);
            }
            int getBaudRate() const{
                return m_baudRate;
            }
            void setDataBits(int dataBits){
                if(dataBits>=5 && dataBits<=8){
                    m_dataBits=dataBits;
                }
                setState(State::Uninitialized);
            }
            int getDataBits() const{
                return m_dataBits;
            }
            void setStopBits(int stopBits){
                if(stopBits>=1 && stopBits<=2){
                    m_stopBits=stopBits;
                }
                setState(State::Uninitialized);
            }
            int getStopBits() const{
                return m_stopBits;
            }
            void setParity(bool parity){
                m_parity=parity;
                setState(State::Uninitialized);
            }
            bool getParity() const{
                return m_parity;
            }

    };
}//namespace az