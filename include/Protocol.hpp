#pragma once

#include <string>

namespace az{

class Protocol {
    public: 
        enum class Type {
            I2C,
            UART,
            SPI
        };
    
        enum class State{
            Ready,
            Uninitialized,
            Error
        };
      /* enum class Status{
            Ok,
            Busy,
            Timeout,
            Error
        };*/

    //virtual void init()=0;
    //virtual void deinit()=0;

    //default destructor
    virtual ~Protocol() = default;

    virtual bool send(const std::string& data)=0; //send data through protocol
    virtual bool receive(std::string& outdata)=0; //receive data through protocol

    
    const std::string& getName() const{
        return m_name;
    };
    Type getType() const{
        return m_type;
    };
    State getState() const{
        return m_state;
    };

    protected:
        //constructor
       Protocol(const std::string& name, Type type):m_name(name), m_type(type), m_state(State::Uninitialized){} 
        bool setState(State newState){
            if(m_state == State::Error){
                return false;
            }
            m_state=newState;
            return true;
        }
     private:
        std::string m_name;
        Type m_type;
        State m_state;
};
} //namespace az