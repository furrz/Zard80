#pragma once

#include "pinbus.h"

/// Z80 -> Arduino Pin-out Mapping is configured here.
/// All pins must be digital.
/// TX, RX, and pin 13 must be left alone.

namespace ZPin
{
    static constexpr PinBus<8> DATA {
        1, 2, 3, 4, 5, 6, 7, 8
    };

    static constexpr PinBus<16> ADDRESS {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    };

    static constexpr int CLK = 0;
    static constexpr int INT = 0;
    static constexpr int NMI = 0;
    static constexpr int HALT = 0;
    static constexpr int MREQ = 0;
    static constexpr int IORQ = 0;
    static constexpr int RFSH = 0;
    static constexpr int M1 = 0;
    static constexpr int RESET = 0;
    static constexpr int BUSRQ = 0;
    static constexpr int WAIT = 0;
    static constexpr int BUSAK = 0;
    static constexpr int WR = 0;
    static constexpr int RD = 0;
}