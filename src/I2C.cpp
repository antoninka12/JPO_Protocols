#include "I2C.hpp"

namespace az{
            I2C::I2C():Protocol("I2C", Type::I2C),
            m_busid(-1), m_deviceAddress(-1), m_SDApin(-1), m_SCLpin(-1), m_frequency(0){}
            //parametrized constructor - I2C can exist in error state if config is invalid
            I2C::I2C(BusID busid, int deviceAddress, int SDApin, int SCLpin, int freq):Protocol("I2C", Type::I2C),
            m_busid(busid), m_deviceAddress(deviceAddress), m_SDApin(SDApin), m_SCLpin(SCLpin), m_frequency(freq){
                if(!isConfigValid()){
                    setState(State::Error);
                    return;
                }
                initHardware();
            }

            I2C::I2C(BusID busid, int deviceAddress, int SDApin, int SCLpin):Protocol("I2C", Type::I2C),
            m_busid(busid), m_deviceAddress(deviceAddress), m_SDApin(SDApin), m_SCLpin(SCLpin), m_frequency(100000){
                if(!isConfigValid()){
                setState(State::Error);
                return;
                }
                initHardware();
            }
            //destructor - deinitializes hardware 
            I2C::~I2C(){
                if (getState() == State::Ready) {
                deinitHardware();
                }
            }
            void I2C::initHardware(){
                setState(State::Ready);
            }
            void I2C::deinitHardware(){
                setState(State::Uninitialized);
            }
            bool I2C::isConfigValid() const {
                return m_busid >= 0 &&
                m_deviceAddress >= 0x08 && 
                m_deviceAddress <= 0x77 &&
                m_SDApin >= 0 &&
                m_SCLpin >= 0 &&
                m_SDApin != m_SCLpin &&
                m_frequency > 0;
            }
            bool I2C::init(){
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
            bool I2C::deinit(){
                if(getState() != State::Ready){
                    return false;
                }
                deinitHardware();
                return getState() == State::Uninitialized;
            }
            bool I2C::send(const std::string& data){ //mozna dodac sprawdzanie czy magistrala jest zajeta
                if(getState() != State::Ready){
                    return false;
                }
                
                const std::size_t byteCount = data.size(); //to zmienic

                if (byteCount < 2) {
                    return false;
                }
                if (byteCount > 32) {
                    return false;
                }
                //sendind data through I2C
                return true;
            }

            bool I2C::receive(std::string& outdata){
                if(getState() != State::Ready){
                    return false;
                }

                outdata="Data through I2C";
                return true;
            }

            //setters and getters
            bool I2C::setBusID(BusID busid){
                if(busid >=0 && busid != m_busid){
                    m_busid=busid;
                    setState(State::Uninitialized);
                    return true;
                }
                return false;
            }
            BusID I2C::getBusID() const{
                return m_busid;
            }
            bool I2C::setDeviceAddress(int deviceAddress){
                if(deviceAddress >= 0x08 && deviceAddress <= 0x77 && deviceAddress != m_deviceAddress){
                    m_deviceAddress=deviceAddress;
                    setState(State::Uninitialized);
                    return true;
                }   
                return false;
            }
            int I2C::getDeviceAddress() const{
                return m_deviceAddress;
            }
            bool I2C::setSDApin(int SDApin){
                if(SDApin >=0 && SDApin != m_SCLpin && SDApin != m_SDApin){
                    m_SDApin=SDApin;
                    setState(State::Uninitialized);
                    return true;
                }
                return false;
            }
            int I2C::getSDApin() const{
                return m_SDApin;
            }
            bool I2C::setSCLpin(int SCLpin){
                if(SCLpin >=0 && SCLpin != m_SDApin && SCLpin != m_SCLpin){
                    m_SCLpin=SCLpin;
                    setState(State::Uninitialized);
                    return true;
                }
                return false;
            }
            int I2C::getSCLpin() const{
                return m_SCLpin;
            }
            bool I2C::setFrequency(int frequency){
                if(frequency >0 && frequency != m_frequency){
                    m_frequency=frequency;
                    setState(State::Uninitialized);
                    return true;
                }
                return false;
            }
            int I2C::getFrequency() const{
                return m_frequency;
            }  
}//namespace az