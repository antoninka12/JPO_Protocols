#include "SPI.hpp"

namespace az{
    SPI::SPI():Protocol("SPI", Type::SPI), 
    m_pinMOSI(-1), 
    m_pinMISO(-1), 
    m_pinSCK(-1), 
    m_pinSS(-1), 
    m_frequency(0), 
    m_mode(Mode::Mode0), 
    m_msbFirst(true){}
    
    SPI::SPI(int pinMOSI, 
        int pinMISO, 
        int pinSCK, 
        int pinSS, 
        int frequency, 
        Mode mode, 
        bool msbFirst):Protocol("SPI", Type::SPI),
        m_pinMOSI(pinMOSI), 
        m_pinMISO(pinMISO),
        m_pinSCK(pinSCK), 
        m_pinSS(pinSS), 
        m_frequency(frequency), 
        m_mode(mode),
        m_msbFirst(msbFirst){
        if(!isConfigValid()){
            setState(State::Error);
            return;
        }
        initHardware();
    }
    
    SPI::SPI(int pinMOSI, 
        int pinMISO, 
        int pinSCK, 
        int pinSS, 
        int frequency, 
        Mode mode):Protocol("SPI", Type::SPI),
        m_pinMOSI(pinMOSI), 
        m_pinMISO(pinMISO),
        m_pinSCK(pinSCK), 
        m_pinSS(pinSS), 
        m_frequency(frequency), 
        m_mode(mode), 
        m_msbFirst(true){
        if(!isConfigValid()){
            setState(State::Error); 
            return;
        }
        initHardware(); 
    }

    SPI::~SPI(){
        if(getState()==State::Ready){ 
            deinitHardware();
        }
    }
    void SPI::initHardware(){  
        setState(State::Ready);
    }
    void SPI::deinitHardware(){ 
        setState(State::Uninitialized);
        m_recvbuffer.clear();
        m_sendbuffer.clear();
    }
    bool SPI::isConfigValid() const{
        return m_pinMOSI >=0 && 
        m_pinMISO >=0 &&
        m_pinSCK >=0 &&
        m_pinSS >=0 && 
        m_frequency >0 &&
        m_pinMOSI != m_pinMISO &&
        m_pinMOSI != m_pinSS &&
        m_pinMOSI != m_pinSCK &&
        m_pinMISO != m_pinSS &&
        m_pinMISO != m_pinSCK &&
        m_pinSCK  != m_pinSS;
    }
    bool SPI::init(){ 
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
    bool SPI::deinit(){
        if(getState() != State::Ready){ 
            return false;
        }
        deinitHardware();
        return getState() == State::Uninitialized;
    }
   
    bool SPI::send(const std::string& data){
        if(getState() != State::Ready){
            return false;
        }
       
       if(data.empty()){
            return false;
        }
        m_sendbuffer.clear();
        m_recvbuffer.clear();
        for(unsigned char c : data){
            m_sendbuffer.push_back(c);
            m_recvbuffer.push_back(~c);
        }
        return true;
    }
    bool SPI::receive(std::string& outdata){
        if(getState() != State::Ready){
            return false;
        }
        if(m_recvbuffer.empty()){
            return false;
        }
        outdata=m_recvbuffer;
        m_recvbuffer.clear();
        return true;
    }


    
    bool SPI::setPinMOSI(int pinMOSI){
        if(pinMOSI >=0 && 
            pinMOSI != m_pinMISO && 
            pinMOSI != m_pinSCK && 
            pinMOSI != m_pinSS && 
            pinMOSI != m_pinMOSI){  
            m_pinMOSI=pinMOSI;
            setState(State::Uninitialized);
            return true;
        } 
        return false;
    }
    int SPI::getPinMOSI() const{
        return m_pinMOSI;
    }
    bool SPI::setPinMISO(int pinMISO){
        if(pinMISO >=0 && 
            pinMISO != m_pinMOSI &&
            pinMISO != m_pinSCK && 
            pinMISO != m_pinSS && 
            pinMISO != m_pinMISO){
            m_pinMISO=pinMISO;
            setState(State::Uninitialized);
            return true;
        }   
        return false;
    }
    int SPI::getPinMISO() const{
        return m_pinMISO;
    }
    bool SPI::setPinSCK(int pinSCK){
        if(pinSCK >=0 && 
            pinSCK != m_pinMOSI && 
            pinSCK != m_pinMISO && 
            pinSCK != m_pinSS && 
            pinSCK != m_pinSCK){
            m_pinSCK=pinSCK;
            setState(State::Uninitialized);
            return true;
        }
        return false;
    }
    int SPI::getPinSCK() const{
        return m_pinSCK;
    }
    bool SPI::setPinSS(int pinSS){
        if(pinSS >=0 && 
            pinSS != m_pinMOSI && 
            pinSS != m_pinMISO && 
            pinSS != m_pinSCK && 
            pinSS != m_pinSS){
            m_pinSS=pinSS;
            setState(State::Uninitialized);
            return true;
        }
        return false;
    }
       
    int SPI::getPinSS() const{
        return m_pinSS;
    }
    bool SPI::setFrequency(int frequency){
        if(frequency >0 && frequency != m_frequency){ 
            m_frequency=frequency;
            setState(State::Uninitialized);
            return true;
        }
        return false;
    }
    int SPI::getFrequency() const{
        return m_frequency;
    }
    bool SPI::setMode(Mode mode) {
        if(mode != m_mode) {
            m_mode = mode;
            setState(State::Uninitialized);
            return true;
        }
        return false;
    }
    SPI::Mode SPI::getMode() const{
        return m_mode;
    }
    bool SPI::setMSBfirst(bool msbFirst){
        if(msbFirst != m_msbFirst){
            m_msbFirst=msbFirst;
            setState(State::Uninitialized);
            return true;
        }
        return false;
    }
    bool SPI::getMSBfirst() const{
        return m_msbFirst;
    }

}