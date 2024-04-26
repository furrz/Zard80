#pragma once

namespace PinUtil
{
    void initPins();
    void pulseClock(int times = 1);
    void pulseClockWhilePinLow(int pin);
    void resetCPU();
}
