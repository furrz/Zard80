#include "pins.h"
#include "event.h"
#include "pinutil.h"
#include "z80mem.h"
#include <Arduino.h>

void setup()
{
    Serial.begin(115200);
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
    const bool m1 = digitalRead(ZPin::M1) == LOW;
    const bool mem = digitalRead(ZPin::MREQ) == LOW;
    const bool io = digitalRead(ZPin::IORQ) == LOW;
    const bool write = digitalRead(ZPin::WR) == LOW;
    const bool read = digitalRead(ZPin::RD) == LOW;
    const bool halt = digitalRead(ZPin::HALT) == LOW;

    if (halt) terminate("HALT was set low");
    if (read && write) terminate("RD and WR cannot be low simultaneously");

    if ((m1 || mem) && read) {
        ZPin::DATA.PinMode(OUTPUT);

        const uint8_t data = address < ZMem::MEMORY_MAX ? ZMem::memory[address] : 0x00;
        ZPin::DATA.Write(data);
        Event::Log(m1 ? Event::EV_FETCH : Event::EV_READ,
                   address, data);

        if (address >= ZMem::MEMORY_MAX) terminate("Memory Operation Out of Range");

        PinUtil::pulseClockWhilePinLow(ZPin::RD);
        ZPin::DATA.PinMode(INPUT);
    } else if (mem && write) {
        const uint8_t data = ZPin::DATA.Read();
        Event::Log(Event::EV_WRITE, address, data);
        if (address < ZMem::MEMORY_MAX) ZMem::memory[address] = data;
        else terminate("Memory Operation Out of Range");
        PinUtil::pulseClockWhilePinLow(ZPin::WR);
    } else if (io && read) {
        ZPin::DATA.PinMode(OUTPUT);
        address &= 0xFF;
        uint8_t result = 0xFF;

        switch (address) {
        case 0:
            // Serial IO Read
            if (Serial.available()) result = Serial.read();
            break;
        default:
            Event::Log(Event::EV_IO_READ, address, result);
            terminate("IO Operation Out of Range");
        }

        ZPin::DATA.Write(result);
        Event::Log(Event::EV_IO_READ, address, result);
        PinUtil::pulseClockWhilePinLow(ZPin::RD);
        ZPin::DATA.PinMode(INPUT);
    } else if (io && write) {
        address &= 0xFF;
        const uint8_t data = ZPin::DATA.Read();

        Event::Log(Event::EV_IO_WRITE, address, data);

        switch (address) {
        case 0:
            // Serial IO Write
            Serial.write(static_cast<char>(data));
            break;
        default:
            terminate("IO Operation Out of Range");
        }

        PinUtil::pulseClockWhilePinLow(ZPin::WR);
    }
}