#pragma once

#include <string>
//dodac noexcept gdzie sie da ???? nodiscard, wrzucic settery i gettery, czemu nie wwszystkie i dlaczego w public/proteceted
//czy cos nie dopisac, np init? albo inne metody wirtualne? to na koniec
/** 
 * \class Protocol
 * \brief Base class for communication protocols
 * 
 * This class is an abstract base class for different communication protocols
 * It provides interfaces for sending and receiving data. It includes State and
 * Type for protocols. 
 * \author Antonia Zdziebko
 */
namespace az{

class Protocol {
    public: 
        /** 
         * An enum.
         * \enum Type
         * \brief Type of communication protocol
         * 
         * Defines the type of communication protcols. 
         * If Type is None, protocol is not initialized 
        */
        enum class Type {
            None, /**< Protocol not initialized*/
            I2C, /**< I2C protocol */
            UART, /**< UART protocol */
            SPI /**< SPI protocol */
        };
        /**
         * An enum.
         * \enum State
         * \brief State of communication protocol
         * It defines state of the protcol.
         */
        enum class State{
            Ready, /**< Protocol is ready to be used */
            Uninitialized, /**< Protocol is not initialized, it isn't ready to be used */
            Error /**< Protocol is in error state */
        };
        /******************************************/
      /* enum class Status{
            Ok,
            Busy,
            Timeout,
            Error
        };*/

    //virtual void init()=0;
    //virtual void deinit()=0;
    //default destructor
     /******************************************/

     /**
     * A destructor.
     * \brief Virtual public destructor in base class- Protocol.
     */
    virtual ~Protocol()=default;
    
    /**
     * A pure virtual function. 
     * \brief Send data through protocol.
     * \param data - data to be sent
    */
    virtual bool send(const std::string& data)=0; //send data through protocol
    /**
     * A pure virtual function. 
     * \brief Receive data through protocol.
     * \param outdata - received data
    */
    virtual bool receive(std::string& outdata)=0; //receive data through protocol
    /**
     * A getter.
     * \brief Get name of the protocol.
     * \return Name of the protocol.
     */
    const std::string& getName() const;
    /**
     * A getter.
     * \brief Get Type of the protocol.
     * \return Type of the protocol.
     */
    Type getType() const;
     /**
     * A getter.
     * \brief Get State of the protocol.
     * \return State of the protocol.
     */
    State getState() const;
    /**
     * Operator == overload.
     * \brief Compares two Protocol objects for equality.
     * \param other - different Protocol object to compare with
     * \return true if both Protocol objects are equal, false if they aren't.
     * Objects are equal if they have the same name and type.
    */
    bool operator==(const Protocol& other) const;
    /** 
    * Operator != overload.
    * \brief Compares two Protocol objects for inequality. 
    * \sa operator== 
    * \param other - different Protocol object to compare with
    * \return true if both Protocol objects are not equal, false if they are equal. 
    * It uses operator== to determine inequality.
    */
    bool operator!=(const Protocol& other) const;

    protected:
        /**
         * Constant expression.
         * Value known at compile time and one for all objects of Protocol class.
         * \brief Default State for Protocol objects.
        */
        static constexpr State defaultState = State::Uninitialized;
        /**
         * Constant expression.
         * Value known at compile time and one for all objects of Protocol class.
         * \brief Default Type for Protocol objects.
        */
        static constexpr Type defaultType = Type::None;
        /**
         * A protected constructor.
         * \brief Default constructor for Protocol class.
         * It can be used by derived classes to expand functionality.
         * 
         * \brief Parametrized constructor for Protocol class.
         * \param name- name of the protocol
         * \param type- type of the protocol
         * Used by derived classes to set specific name and type of protocol.
        */
        Protocol(); /**< Default constructor */
       Protocol(const std::string& name, Type type); /**< Parametrized constructor */
       /**
        * A protected setter.
        * \brief Set State of the protocol.
        * \param newState - new State to be set
        * \return true if setting State was successful, false otherwise.
        * Can be used only by derived classes to check the tranistion rules.
        * If state is Error, it can only be changed to Uninitialized.
        */
       bool setState(State newState);
     private:
        /**
         * \brief name of the protocol
         * Represents the name of individual protocol.
         * It is set during when object is created and cannot be changed afterwards.
         */
        std::string m_name;
        /**
         * \brief type of the protocol
         * Represents the type of individual protocol.
         * It is set during when object is created and cannot be changed afterwards.
         */
        Type m_type;
        /**
         * \brief state of the protocol
         * Represents the current state of individual protocol.
         * It can be changed using setState method but only by derived classes in controlled way.
         */
        State m_state;
};
} //namespace az