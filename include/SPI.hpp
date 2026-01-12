#pragma once
#include "Protocol.hpp"
//w zwykłym konstruktorze w jakims stanie? jak zrobic init? reiinit? w jakim stanie jest jak stworzymy domyslny, potem ustawimy to bedzie uninitialized, ale trzeba zrobic init, a jest prywatne
namespace az{
    /**
     * \class SPI 
     * \brief SPI communication protocol class.
     * It dereives form Protocol base class.
     * It provides methods for configurating, initializing, sending and receiving data
     * through SPI protocol.
     * It includes fields specific for SPI protocol. F.e. pins, frequency.
     * \author Antonia Zdziebko
     */
    class SPI: public Protocol{
        public: 
            /** 
             * \enum Mode
             * \brief SPI communication mode
             * It defines the mode of SPI communication.
             * Provides logical representation of SPI modes, used in software.
             * It does not directly correspond to hardware settings.
            */
            enum class Mode{
                    Mode0=0, /**< Logical representation of real Mode0 in SPI*/
                    Mode1=1, /**< Logical representation of real Mode1 in SPI*/
                    Mode2=2, /**< Logical representation of real Mode2 in SPI*/
                    Mode3=3  /**< Logical representation of real Mode3 in SPI*/
                };
        private:
            /**
             * \brief SPI specific fields
             * They represent standard configuration for SPI protocol.
            */
            int m_pinMOSI; /**< MOSI pin number */
            int m_pinMISO; /**< MISO pin number */
            int m_pinSCK;  /**< SCK pin number */
            int m_pinSS;   /**< SS pin number */
            int m_frequency; /**< clock frequency in Hz */
            Mode m_mode; /**<Logical SPI mode */
            bool m_msbFirst;/**< True if MSB is transmiteed first */
            
            /**
             * Private methods.
             * \brief Logical initialization of SPI.
             * It sets the state to Ready.
             * It does not interact with hardware directly.
             * Used only in controlled way.
             */
            void initHardware();
            /**
             * \brief Logical deinitialization of SPI.
             * It sets the state to Uninitialized.
             * It does not interact with hardware directly.
             * Used only in controlled way.
             */
            void deinitHardware();
            /**
             * \brief Validating current configuration of SPI.
             * \return true if configuration is valid, false otherwise.
             * Used to check if SPI can be initialized with current configuration.
             * It check configuration of pins and frequency.
             */
            bool isConfigValid() const;

        public:
            /** 
            * \brief Constructors of SPI class
            * Used to create and destroy SPI objects.
            */
            SPI(); /**< Default constructor, pins are set to -1, frequency to 0, mode to Mode0, msbFirst to true */
            SPI(int pinMOSI, 
                int pinMISO,
                int pinSCK,
                int pinSS,
                int frequency,
                Mode mode,
                bool msbFirst); /**<Parametrized constructor, setting all pins, frequency, mode and msbFirst */
            SPI(int pinMOSI,
                int pinMISO,
                int pinSCK,
                int pinSS,
                int frequency,
                Mode mode); /**<Parametrized constructor, setting all pins, frequency and mode, msbFirst set to true*/
            /**
             * \brief Destructor of SPI class.
             * Deinitialization of SPI in logical way if state is Ready.
            */
            ~SPI() override; 

            /**
             * \brief Send data through SPI.
             * It provides logical implementation of sending data through SPI.
             * Checks if state is Ready before sending data.
             * Checks if data is empty.
             * \return return true if the SPI is in Rady state and the data is not empty, false otherwise.
             * \param data - data to be sent
             */
            bool send(const std::string& data) override;
            /**
             * \brief Recive data through SPI.
             * It provides logical implementation of receiving data through SPI.
             * Checks if state is Ready before reciving data.
             * \return true if state is ready, false otherwise.
             * \param outdata - received data
             */
            bool receive(std::string& outdata) override;
            /**
             * \brief Function for logicial initializing and reinitializing of SPI protocol.
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
             * \brief Function for logical deinitializing SPI object.
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
            bool setPinMOSI(int pinMOSI); /**< Setting MOSI pin for SPI if it is valid*/
            int getPinMOSI() const; /**< Getting MOSI pin */

            bool setPinMISO(int pinMISO);/**< Setting MISO pin for SPI if it is valid*/
            int getPinMISO() const;/**< Getting MISO pin */

            bool setPinSCK(int pinSCK);/**< Setting SCK pin for SPI if it is valid*/
            int getPinSCK() const;/**< Getting SCK pin */

            bool setPinSS(int pinSS);/**< Setting SS pin for SPI if it is valid*/
            int getPinSS() const;/**< Getting SS pin */

            bool setFrequency(int frequency);/**< Setting frequency of clock for SPI if it is valid*/
            int getFrequency() const;/**< Getting frequency in Hz */

            bool setMode(Mode mode);/**< Setting SPI mode if it is valid*/
            Mode getMode() const;/**< Getting SPI mode*/

            bool setMSBfirst(bool msbFirst);/**< Setting msbFirst bit - true: MSB first, false otherwise*/
            bool getMSBfirst() const;/**< Getting true if MSB is transmited first, false otherwise */
    };
}