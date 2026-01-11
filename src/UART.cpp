#include "UART.hpp"

namespace az{
            //default constructor
            UART::UART():Protocol("UART", Type::UART),m_pinTx(-1), m_pinRx(-1), m_baudRate(0), m_dataBits(0), m_stopBits(0), m_parity(false){}
            //parametrized constructor
            UART::UART(int pinTx, int pinRx, int baudRate, int dataBits, int stopBits):Protocol("UART", Type::UART),m_pinTx(pinTx), m_pinRx(pinRx), m_baudRate(baudRate), 
            m_dataBits(dataBits), m_stopBits(stopBits){
                if(!isConfigValid()){
                    setState(State::Error);
                    return;
                }
                initHardware();
            }
            //parametrized constructor with parity
            UART::UART(int pinTx, int pinRx, int baudRate, int dataBits, int stopBits, bool parity):Protocol("UART", Type::UART),m_pinTx(pinTx), m_pinRx(pinRx), m_baudRate(baudRate), 
            m_dataBits(dataBits), m_stopBits(stopBits), m_parity(parity){
                if(!isConfigValid()){
                    setState(State::Error);
                    return;
                }
                initHardware();
            }
            //destructor
            UART::~UART(){
                if(getState()==State::Ready){
                    deinitHardware();
                }
            }
            void UART::initHardware(){
                setState(State::Ready);
            }
             void UART::deinitHardware(){
                setState(State::Uninitialized);
            }
            bool UART::isConfigValid() const{
                return m_pinTx>=0 && 
                m_pinRx>=0 && 
                m_baudRate>0 &&
                m_dataBits>=5 && 
                m_dataBits<=8 && 
                m_stopBits>=1 &&
                m_stopBits<=2;
            }
            bool UART::init(){
                if(getState() == State::Ready){
                    return true;
                }
                if(!isConfigValid()){
                    setState(State::Error);
                    return false;
                }
                initHardware();
                return getState() == State::Ready;
            }
            bool UART::deinit(){
                if(getState() != State::Ready){
                    return false;
                }
                deinitHardware();
                return getState() == State::Uninitialized;
            }
            bool UART::send(const std::string& data){
                if(getState() != State::Ready){
                    return false;
                }
                if(data.empty()){
                    return false;
                }
                //sendind data through UART
                return true;
            }
            bool UART::receive(std::string& outData){
                if(getState() != State::Ready){
                    return false;
                }

                outData="Data through UART";
                return true;
            }

            //setters and getters
            void UART::setPinTx(int pinTx){
                if(pinTx>=0 && pinTx!=m_pinRx && pinTx!=m_pinTx){
                    m_pinTx=pinTx;
                    setState(State::Uninitialized);
                }
            }
            int UART::getPinTx() const{
                return m_pinTx;
            }
            void UART::setPinRx(int pinRx){
                if(pinRx>=0 && pinRx!=m_pinTx && pinRx!=m_pinRx){
                    m_pinRx=pinRx;
                    setState(State::Uninitialized);
                }
              
            }
            int UART::getPinRx() const{
                return m_pinRx;
            }
            void UART::setBaudRate(int baudRate){
                if(baudRate>0 && baudRate!=m_baudRate){
                    m_baudRate=baudRate;
                    setState(State::Uninitialized);
                }
            }
            int UART::getBaudRate() const{
                return m_baudRate;
            }
            void UART::setDataBits(int dataBits){
                if(dataBits>=5 && dataBits<=8 && dataBits!=m_dataBits){
                    m_dataBits=dataBits;
                    setState(State::Uninitialized);
                } 
            }
            int UART::getDataBits() const{
                return m_dataBits;
            }
            void UART::setStopBits(int stopBits){
                if(stopBits>=1 && stopBits<=2 && stopBits!=m_stopBits){
                    m_stopBits=stopBits;
                    setState(State::Uninitialized);
                }
            }
            int UART::getStopBits() const{
                return m_stopBits;
            }
            void UART::setParity(bool parity){
                if(parity != m_parity){
                m_parity=parity;
                setState(State::Uninitialized);
                }
            }
            bool UART::getParity() const{
                return m_parity;
            }
}//namespace az