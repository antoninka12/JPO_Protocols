#pragma once
#include "Protocol.hpp"
//w zwykłym konstruktorze w jakims stanie? jak zrobic init? reiinit? w jakim stanie jest jak stworzymy domyslny, potem ustawimy to bedzie uninitialized, ale trzeba zrobic init, a jest prywatne
namespace az{
    class SPI: public Protocol{
        public: 
        enum class Mode{
                Mode0=0,
                Mode1=1,
                Mode2=2,
                Mode3=3
            };
        private:
            int m_pinMOSI;
            int m_pinMISO;
            int m_pinSCK;
            int m_pinSS;
            int m_frequency;
            Mode m_mode;
            bool m_msbFirst;

            void initHardware();
            void deinitHardware();
            bool isConfigValid() const;

        public:
            //default constructor
            SPI();
            //parametrized constructor
            SPI(int pinMOSI,
                int pinMISO,
                int pinSCK,
                int pinSS,
                int frequency,
                Mode mode,
                bool msbFirst);
            //parametrized constructor without msbFirst
            SPI(int pinMOSI,
                int pinMISO,
                int pinSCK,
                int pinSS,
                int frequency,
                Mode mode);
            //destructor
            ~SPI() override;
            
            //public methods:
            bool send(const std::string& data) override;
            bool receive(std::string& outdata) override;
            bool init();
            bool deinit();

            //setters and getters
            void setPinMOSI(int pinMOSI);
            int getPinMOSI() const;

            void setPinMISO(int pinMISO);
            int getPinMISO() const;

            void setPinSCK(int pinSCK);
            int getPinSCK() const;

            void setPinSS(int pinSS);
            int getPinSS() const;

            void setFrequency(int frequency);
            int getFrequency() const;

            void setMode(Mode mode);
            Mode getMode() const;

            void setMSBfirst(bool msbFirst);
            bool getMSBfirst() const;
    };
}