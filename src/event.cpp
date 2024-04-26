#include <Arduino.h>
#include "event.h"

namespace Event
{
    struct Event
    {
        EventType type;
        uint16_t address;
        uint8_t data;
    };

    Event events[MAX_EVENTS];
    uint16_t num_events = 0;

    void Log(EventType type, uint16_t address, uint8_t data)
    {
        if (num_events == MAX_EVENTS) return;
        events[num_events].type = type;
        events[num_events].address = address;
        events[num_events].data = data;
        num_events++;
    }

    void PrintAll()
    {
        Serial.println("[Zard80] EVENT ADDRESS  DATA");
        for (uint16_t i = 0; i < num_events; i++) {
            Serial.print("[Zard80] ");
            switch (events[i].type) {
            case EV_READ: Serial.print("READ  ");
                break;
            case EV_WRITE: Serial.print("WRITE ");
                break;
            case EV_FETCH: Serial.print("FETCH ");
                break;
            case EV_IO_READ: Serial.print("IO RD ");
                break;
            case EV_IO_WRITE: Serial.print("IO WR ");
                break;
            }

            char buf[12] = { 0 };
            sprintf(buf, "%08x ", events[i].address);
            Serial.print(buf);
            sprintf(buf, "%04x", events[i].data);
            Serial.println(buf);
        }
    }
}