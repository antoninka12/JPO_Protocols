#pragma once

#include "Protocol.hpp"

namespace az{
    //???
    using BusID=int; 
    /**
     * \class I2C
     * \brief I2C communication protocol class.
     * It dereives form Protocol base class.
     * It provides methods for configurating, initializing, sending and receiving data
     * through I2C protocol.
     * It includes fields specific for I2C protocol. F.e. pins, busID, frequency and Device Address.
     * \author Antonia Zdziebko
     */
    class I2C : public Protocol{
        private:
            /**
             * \brief I2C specific fields
             * They represent standard configuration for I2C protocol.
            */
            BusID m_busid; /**< */
            int m_deviceAddress; /**<Specific addres for device in I2C protocol */
            int m_SDApin; /**<SDA pin number */
            int m_SCLpin; /**<SCL pin number */
            int m_frequency; /**<Clock frequency in Hz */
             /**
             * Private methods.
             * \brief Logical initialization of I2C.
             * It sets the state to Ready.
             * It does not interact with hardware directly.
             * Used only in controlled way.
             */
            void initHardware();
            /**
             * \brief Logical deinitialization of I2C.
             * It sets the state to Uninitialized.
             * It does not interact with hardware directly.
             * Used only in controlled way.
             */
            void deinitHardware();
             /**
             * \brief Validating current configuration of I2C parameters.
             * \return true if configuration is valid, false otherwise.
             * Used to check if I2C can be initialized with current configuration.
             * It check configuration of pins, addresses, bus ID and frequency.
             */
            bool isConfigValid() const;
        public: 
            /** 
            * \brief Constructors of SPI class
            * Used to create and destroy SPI objects.
            */
            I2C();/**< Default constructor, pins and addresses are set to -1, frequency to 0*/
            I2C(BusID busid, int deviceAddress, int SDApin, int SCLpin, int freq);/**<Parametrized constructor, 
            setting all pins, frequency, busID, device Address */

            I2C(BusID busid, int deviceAddress, int SDApin, int SCLpin);/**<Parametrized constructor, 
            setting all pins, frequency to 100kHz, busID, device Address */
            
             /**
             * \brief Destructor of I2C class.
             * Deinitialization of I2C in logical way if state is Ready.
            */
            ~I2C() override;

            /**
             * \brief Send data through I2C.
             * It provides logical implementation of sending data through I2C.
             * Checks if state is Ready before sending data.
             * Checks if byteCount is correct.
             * \return return true if the I2C is in Rady state and size of data is correct.
             * \param data - data to be sent
             */
            bool send(const std::string& data) override;
            /**
             * \brief Recive data through I2C.
             * It provides logical implementation of receiving data through I2C.
             * Checks if state is Ready before reciving data.
             * \return true if state is ready, false otherwise.
             * \param outdata - received data
             */
            bool receive(std::string& outdata) override;
            /**
             * \brief Function for logicial initializing and reinitializing of I2C protocol.
             * \sa isConfigValid().
             * \sa initHardware()
             * Before initializing it checks configuration and sets State to Error if isn't valid.
             * Uses private method initHardware() to initialize in controlled way. 
             * Sets state to Ready if it went thgrough validation.
             * Checks if object isn't already initialized.
             * \return true if state is set to Ready, false otherwise.
             */
            bool init();
            /**
             * \brief Function for logical deinitializing I2C object.
             * \sa initHardware()
             * It uses initHardware() for deinitializing.
             * Sets state to Uninitilized if the state was Ready.
             * \return Return true if state is set to uninitialized, false otherwise.
             */
            bool deinit();
             /** 
             * Setters and geters
             * \brief Setting and getting all private fields.
            */
            bool setBusID(BusID busid); /**<Setting BusID, checking if input value is correct */
            BusID getBusID() const; /**<Getting BusID */

            bool setDeviceAddress(int deviceAddress);/**<Setting Addr of Device, checking if input value is correct*/
            int getDeviceAddress() const;/**<Getting Addres of Device */

            bool setSDApin(int SDApin); /**<Setting SDApin, checking if input value is correct*/
            int getSDApin() const;/**<Getting SDA pin */

            bool setSCLpin(int SCLpin);/**<Setting SCLpin, checking if input value is correct*/
            int getSCLpin() const;/**<Getting SCL pin */

            bool setFrequency(int frequency);/**<Setting frequency, checking if input value is correct*/
            int getFrequency() const;/**<Getting frequency of clock*/
    };
}//namespace az