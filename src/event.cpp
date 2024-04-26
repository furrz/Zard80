#include <Arduino.h>
#include "event.h"

namespace Event
{
    struct Event
    {
        unsigned long event_number;
        EventType type;
        uint16_t address;
        uint8_t data;
    };

    static unsigned long event_count = 0;

    static Event initial_events[MAX_INITIAL_EVENTS] {};
    static uint16_t num_initial_events = 0;

    static Event recent_events[MAX_RECENT_EVENTS] {};
    static uint16_t recent_events_start = 0;
    static uint16_t recent_events_end = 0;

    static char print_buf[36] { };

    void Log(const EventType type, const uint16_t address, const uint8_t data)
    {
        Event* pEvent;
        if (num_initial_events < MAX_INITIAL_EVENTS) {
            pEvent = &initial_events[num_initial_events];
            num_initial_events++;
        } else {
            pEvent = &recent_events[recent_events_end];
            recent_events_end = (recent_events_end + 1) % MAX_RECENT_EVENTS;
            if (recent_events_end == recent_events_start) recent_events_start = (recent_events_start + 1) % MAX_RECENT_EVENTS;
        }

        pEvent->event_number = event_count++;
        pEvent->type = type;
        pEvent->address = address;
        pEvent->data = data;
    }

    void PrintEvent(const Event* event) {
        auto type_name = "????? ";
        switch (event->type) {
            case EV_READ: type_name = "READ  ";
            break;
            case EV_WRITE: type_name = "WRITE ";
            break;
            case EV_FETCH: type_name = "FETCH ";
            break;
            case EV_IO_READ: type_name = "IO RD ";
            break;
            case EV_IO_WRITE: type_name = "IO WR ";
            break;
        }

        sprintf(print_buf, "[Zard80]   %8lu %s %04x %02x", event->event_number, type_name, event->address, event->data);
        Serial.println(print_buf);
    }

    void PrintAll()
    {
        Serial.println("[Zard80] EVENT #    EVENT ADDRESS  DATA");

        for (uint16_t i = 0; i < num_initial_events; i++) {
            PrintEvent(&initial_events[i]);
        }

        if (recent_events_start != recent_events_end) {
            Serial.println("[Zard80] ...");
            for (uint16_t i = recent_events_start; i != recent_events_end; i = (i + 1) % MAX_RECENT_EVENTS) {
                PrintEvent(&recent_events[i]);
            }
        }
    }
}