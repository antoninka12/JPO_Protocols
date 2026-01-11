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
            void initHardware();
            void deinitHardware();
            bool isConfigValid() const;
        public: //we dont use protected bcs i2c is final class
            //default constructor
            I2C();
            //parametrized constructor - I2C can exist in error state if config is invalid
            I2C(BusID busid, int deviceAddress, int SDApin, int SCLpin, int freq);

            I2C(BusID busid, int deviceAddress, int SDApin, int SCLpin);
            //destructor - deinitializes hardware 
            ~I2C() override;

            bool send(const std::string& data) override;
            bool receive(std::string& outdata) override;
            bool init();
            bool deinit();
            //setters and getters
            void setBusID(BusID busid);
            BusID getBusID() const;

            void setDeviceAddress(int deviceAddress);
            int getDeviceAddress() const;
            void setSDApin(int SDApin);
            int getSDApin() const;
            void setSCLpin(int SCLpin);
            int getSCLpin() const;
            void setFrequency(int frequency);
            int getFrequency() const;
    };
}//namespace az