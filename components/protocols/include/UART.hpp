#pragma once
#include "Protocol.hpp"

namespace az{
    /**
     * \class UART
     * \brief UART communication protocol class.
     * It dereives form Protocol base class.
     * It provides methods for configurating, initializing, sending and receiving data
     * through UART protocol.
     * It includes fields specific for UART protocol. F.e. pins, baud rate.
     * \author Antonia Zdziebko
     */
    class UART : public Protocol{
        private:
             /**
             * \brief UART specific fields
             * They represent standard configuration for UART protocol.
            */
            int m_pinTx; /**< Tx pin number */
            int m_pinRx;/**< Rx pin number */
            int m_baudRate; /**< UART baudrate */
            int m_dataBits; /* number of data bits per frame (valid: 5-8)*/
            int m_stopBits; /**< number of stop bits (1 or 2) */
            bool m_parity; /**<parity bit: true-even, false-odd*/

            std::string m_sendbuffer;/**< Logical representation of transmit buffer, it stores data for sending */
            std::string m_recvbuffer; /**< Logical representation of receive buffer, stores received data */
            /**
             * Private methods.
             * \brief Logical initialization of UART protocol.
             * It sets the state to Ready.
             * It does not interact with hardware directly.
             * Used only in controlled way.
             */
            void initHardware();
            /**
             * \brief Logical deinitialization of UART protocol.
             * It sets the state to Uninitialized.
             * It does not interact with hardware directly.
             * Used only in controlled way.
             */
            void deinitHardware();
            /**
             * \brief Validating current configuration of UART protocol.
             * \return true if configuration is valid, false otherwise.
             * Used to check if SPI can be initialized with current configuration.
             * It check configuration of pins, baudRate, data and stop bits.
             */
            bool isConfigValid() const;
        public:
            /** 
            * \brief Constructors of UART class
            * Used while creating UART objects.
            */
            UART();/**< Default constructor, pins are set to -1, 
                * parity to false, the rest is 0*/
            UART(int pinTx, 
                int pinRx, 
                int baudRate, 
                int dataBits, 
                int stopBits);/**<Parametrized constructor,
                *setting all pins, and number ofdata/stop bits, parity to false*/
            UART(int pinTx, 
                int pinRx, 
                int baudRate, 
                int dataBits, 
                int stopBits, 
                bool parity); /**<Parametrized constructor, 
                * setting all pins, and number of data/stop bits, parity*/
            /**
             * \brief Destructor of UART class.
             * Deinitialization of UART in logical way if state is Ready.
            */
            ~UART() override;
             /**
             * \brief Send data through UART.
             * It provides logical implementation of sending data through UART.
             * Checks if state is Ready before sending data.
             * Checks if data is empty.
             * Check if in data is sign '\0', skipping if occurs.
             * \return return true if the UART is in Ready state and the data is not empty, false otherwise.
             * \param data - data to be sent
             */
            bool send(const std::string& data) override;
              /**
             * \brief Recive data through UART.
             * It provides logical implementation of receiving data through UART.
             * Checks if state is Ready before reciving data.
             * \return true if state is ready, false otherwise.
             * \param outdata - received data
             */
            bool receive(std::string& outData) override;
            /**
             * \brief Function for logicial initializing and reinitializing of UART protocol.
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
             * \brief Function for logical deinitializing UART object.
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
            bool setPinTx(int pinTx); /**<Setting Tx pin in configuration if input is valid*/
            int getPinTx() const; /**< Getting Tx pin */

            bool setPinRx(int pinRx); /**<Setting Rx pin in configuration if input is valid*/
            int getPinRx() const; /**< Getting Rx pin */

            bool setBaudRate(int baudRate); /**<Setting baudRate in configuration if input is valid*/
            int getBaudRate() const; /**< Getting baudRate */
 
            bool setDataBits(int dataBits); /**<Setting number od data Bits in configuration if input is valid*/
            int getDataBits() const; /**< Getting number of data bits */

            bool setStopBits(int stopBits); /**<Setting number of stop Bits in configuration if input is valid*/
            int getStopBits() const; /**<  Getting number of stop bits */

            bool setParity(bool parity); /**<Setting parity in configuration if input is valid*/
            bool getParity() const; /**< Getting parity*/
 
    };
}//namespace az