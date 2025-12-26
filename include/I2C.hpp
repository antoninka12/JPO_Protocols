#pragma once

#include "Protocol.hpp"
//reinit moze dodac?????
namespace az{
    using BusID=int; 
    class I2C : public Protocol{
        private:
            BusID m_busid;
            int m_deviceAddress;
            int m_SDApin;
            int m_SCLpin;
            int m_frequency;
            void initHardware(){
                setState(State::Ready);
            }
            void deinitHardware(){
                setState(State::Uninitialized);
            }
            bool isConfigValid() const {
                return m_busid >= 0 &&
                m_deviceAddress >= 0x08 && m_deviceAddress <= 0x77 &&
                m_SDApin >= 0 &&
                m_SCLpin >= 0 &&
                m_SDApin != m_SCLpin &&
                m_frequency > 0;
            }
        public: //we dont use protected bcs i2c is final class
            //default constructor
            I2C():Protocol("I2C", Type::I2C),
            m_busid(-1), m_deviceAddress(-1), m_SDApin(-1), m_SCLpin(-1), m_frequency(0){}
            //parametrized constructor - I2C can exist in error state if config is invalid
            I2C(BusID busid, int deviceAddress, int SDApin, int SCLpin, int freq):Protocol("I2C", Type::I2C),
            m_busid(busid), m_deviceAddress(deviceAddress), m_SDApin(SDApin), m_SCLpin(SCLpin), m_frequency(freq){
                if(!isConfigValid()){
                    setState(State::Error);
                    return;
                }
                initHardware();
            }

            I2C(BusID busid, int deviceAddress, int SDApin, int SCLpin):Protocol("I2C", Type::I2C),
            m_busid(busid), m_deviceAddress(deviceAddress), m_SDApin(SDApin), m_SCLpin(SCLpin), m_frequency(100000){
                if(!isConfigValid()){
                setState(State::Error);
                return;
                }
                initHardware();
            }
            //destructor - deinitializes hardware 
            ~I2C() override {
                if (getState() == State::Ready) {
                deinitHardware();
                }
            }
            bool send(const std::string& data) override{
                if(getState() != State::Ready){
                    return false;
                }
                if(data.empty()){
                    return false;
                }
                //sendind data through I2C
                return true;
            }

            bool receive(std::string& outdata) override{
                if(getState() != State::Ready){
                    return false;
                }

            outdata="Data tgrough I2C";
            return true;
            }

            //setters and getters
            void setBusID(BusID busid){
                if(busid >=0){
                    m_busid=busid;
                }
                setState(State::Uninitialized);
            }
            BusID getBusID() const{
                return m_busid;
            }
            void setDeviceAddress(int deviceAddress){
                if(deviceAddress >= 0x08 && deviceAddress <= 0x77){
                    m_deviceAddress=deviceAddress;
                }
                setState(State::Uninitialized);
            }
            int getDeviceAddress() const{
                return m_deviceAddress;
            }
            void setSDApin(int SDApin){
                if(SDApin >=0 && SDApin != m_SCLpin){
                    m_SDApin=SDApin;
                }
                setState(State::Uninitialized);
            }
            int getSDApin() const{
                return m_SDApin;
            }
            void setSCLpin(int SCLpin){
                if(SCLpin >=0 && SCLpin != m_SDApin){
                    m_SCLpin=SCLpin;
                }
                setState(State::Uninitialized);
            }
            int getSCLpin() const{
                return m_SCLpin;
            }
            void setFrequency(int frequency){
                if(frequency >0){
                    m_frequency=frequency;
                }
                setState(State::Uninitialized);
            }
            int getFrequency() const{
                return m_frequency;
            }
    };   
}