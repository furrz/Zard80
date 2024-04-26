#pragma once

#include "pinbus.h"

/// Z80 -> Arduino Pin-out Mapping is configured here.
/// All pins must be digital.
/// TX, RX, and pin 13 must be left alone.

namespace ZPin
{
    static constexpr PinBus<8> DATA {
        2, 3, 4, 5, 6, 7, 8, 9
    };

    static constexpr PinBus<16> ADDRESS {
        30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45
    };

    static constexpr int CLK = 11;
    static constexpr int INT = 51;
    static constexpr int NMI = 50;
    static constexpr int HALT = 49;
    static constexpr int MREQ = 46;
    static constexpr int IORQ = 48;
    static constexpr int RFSH = 52;
    static constexpr int M1 = 53;
    static constexpr int RESET = 26;
    static constexpr int BUSRQ = 22;
    static constexpr int WAIT = 47;
    static constexpr int BUSAK = 23;
    static constexpr int WR = 24;
    static constexpr int RD = 25;
}