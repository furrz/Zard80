#include "pins.h"
#include "event.h"
#include "pinutil.h"
#include <Arduino.h>

#define MEMORY_MAX 2048
uint8_t memory[MEMORY_MAX] = {
};

void setup()
{
    Serial.begin(9600);
    while (!Serial) {}

    Serial.println("[Zard80] Online\n");

    PinUtil::initPins();
    PinUtil::resetCPU();
}

[[noreturn]] void terminate(const char *reason)
{
    Serial.print("[Zard80] Terminating: ");
    Serial.println(reason);
    Event::PrintAll();

    for (;;) {}
}

void loop()
{
    PinUtil::pulseClock();

    uint16_t address = ZPin::ADDRESS.Read();
    bool m1 = digitalRead(ZPin::M1) == LOW;
    bool mem = digitalRead(ZPin::MREQ) == LOW;
    bool io = digitalRead(ZPin::IORQ) == LOW;
    bool write = digitalRead(ZPin::WR) == LOW;
    bool read = digitalRead(ZPin::RD) == LOW;
    bool halt = digitalRead(ZPin::HALT) == LOW;

    if (halt) terminate("HALT was set low");
    if (read && write) terminate("RD and WR cannot be low simultaneously");

    if ((m1 || mem) && read) {
        ZPin::DATA.PinMode(OUTPUT);
        ZPin::DATA.Write(memory[address % MEMORY_MAX]);
        Event::Log(m1 ? Event::EV_FETCH : Event::EV_READ,
                   address,
                   memory[address % MEMORY_MAX]);
        // TODO: Do we need to pulse once with WAIT low? Try without, first.
        PinUtil::pulseClockWhilePinLow(ZPin::RD);
        ZPin::DATA.PinMode(INPUT);
    } else if (mem && write) {
        memory[address % MEMORY_MAX] = ZPin::DATA.Read();
        Event::Log(Event::EV_WRITE, address, memory[address % MEMORY_MAX]);
        PinUtil::pulseClockWhilePinLow(ZPin::WR);
    } else if (io && read) {
        ZPin::DATA.PinMode(OUTPUT);
        address &= 0xFF;

        uint8_t result = 0xFF;

        switch (address) {
        case 0:
            // IO Read
            if (Serial.available()) result = Serial.read();
            break;
        default:break;
        }

        ZPin::DATA.Write(result);
        Event::Log(Event::EV_IO_READ, address, result);
        PinUtil::pulseClockWhilePinLow(ZPin::RD);
        ZPin::DATA.PinMode(INPUT);
    } else if (io && write) {
        address &= 0xFF;
        uint8_t data = ZPin::DATA.Read();

        switch (address) {
        case 0:Serial.write((char) data);
            break;
        default:break;
        }

        Event::Log(Event::EV_IO_WRITE, address, data);
        PinUtil::pulseClockWhilePinLow(ZPin::WR);
    }

    terminate("Not Implemented");
}