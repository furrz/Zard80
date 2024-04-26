#pragma once

#include <stdint.h>

/// CPU Event Logging
namespace Event
{
    constexpr int MAX_EVENTS = 128;

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
