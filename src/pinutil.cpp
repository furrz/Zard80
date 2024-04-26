#include "pinutil.h"
#include "pins.h"

void PinUtil::initPins()
{
    constexpr int outputsActiveLow[] = {
        ZPin::BUSRQ,
        ZPin::CLK,
        ZPin::INT,
        ZPin::NMI,
        ZPin::RESET,
        ZPin::WAIT
    };

    for (const auto& item: outputsActiveLow) {
        pinMode(item, OUTPUT);
        digitalWrite(item, HIGH);
    }
}

void PinUtil::pulseClock(int times)
{
    for (int i = 0; i < times; i++) {
        digitalWrite(ZPin::CLK, LOW);
        digitalWrite(ZPin::CLK, HIGH);
    }
}

void PinUtil::pulseClockWhilePinLow(int pin)
{
    while (digitalRead(pin) == LOW) pulseClock();
}

void PinUtil::resetCPU()
{
    digitalWrite(ZPin::RESET, LOW);
    pulseClock(3);
    digitalWrite(ZPin::RESET, HIGH);
}
