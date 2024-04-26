#pragma once

#include <stdint.h>

/// CPU Event Logging: Logs requests from the Z80 to the Arduino.
namespace Event
{
    /// Maximum buffer of events logged immediately after startup.
    constexpr unsigned MAX_INITIAL_EVENTS = 128;

    /// Maximum ring buffer of recently logged events.
    constexpr unsigned MAX_RECENT_EVENTS = 128;

    /// Unsigned of CPU Event
    enum EventType
    {
        EV_READ,
        EV_WRITE,
        EV_FETCH,
        EV_IO_READ,
        EV_IO_WRITE
    };

    void Log(EventType type, uint16_t address, uint8_t data);
    void PrintAll();
}
