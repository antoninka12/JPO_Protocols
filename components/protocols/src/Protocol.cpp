#include "Protocol.hpp"

namespace az{
    Protocol::Protocol():m_name("Unknown"), m_type(defaultType), m_state(defaultState){}
    Protocol::Protocol(const std::string& name, Type type):m_name(name), m_type(type), m_state(defaultState){} 
    
    const std::string& Protocol::getName() const{
        return m_name;
    }
    Protocol::Type Protocol::getType() const{
        return m_type;
    }
    Protocol::State Protocol::getState() const{
        return m_state;
    }
    bool Protocol::setState(State newState){
        if(m_state == State::Error && newState != State::Uninitialized){ 
                return false;
        }
        m_state=newState;
        return true;
    }
    bool Protocol::operator==(const Protocol& other) const{
        return (m_name== other.m_name)&& (m_type== other.m_type);
    }
    bool Protocol::operator!=(const Protocol& other) const{
        return !operator==(other);
    }
} //namespace az