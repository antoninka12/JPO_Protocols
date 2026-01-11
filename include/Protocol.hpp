#pragma once

#include <string>

namespace az{

class Protocol {
    public: 
        enum class Type {
            None,
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

    
    const std::string& getName() const;
    Type getType() const;
    State getState() const;

    protected:
        static constexpr State defaultState = State::Uninitialized; //static to jedna wartosc dla całej klasy - dla wszytstkich obiektów
        static constexpr Type defaultType = Type::None; //a constexpr to wartosc stała znana w czasie kompilacji
        //constructor
        Protocol() = default; //default constructor
       Protocol(const std::string& name, Type type);
       bool setState(State newState);
     private:
        std::string m_name;
        Type m_type;
        State m_state;
};
} //namespace az