<img align="right" src="ReadmePhoto.jpg" width="400" alt="A picture of the Z80 wired to an Arduino Mega."/>

# Zard80
*Run your Z80 with only an Arduino Mega or similar.*

---

Zard80 is simple: Just wire up every pin on your Z80 to an available digital pin on your Arduino (except VCC and GND,
obviously!) and you're good to go!

This should work for modern, CMOS-based Z80s - older NMOS chips reportedly don't appreciate being severely
under-clocked.

If running outside of PlatformIO, Set your Serial Monitor's baud rate to 115200.

## Configuration

Details like Arduino pinout, system memory size, and debug event logging are configurable:
 - Edit `include/pins.h` to remap the pinout.
 - Edit `include/z80mem.h` to change the memory size.
 - Edit `include/event.h` to change debug event logging capacity.

## Behaviour

Before starting the Z80, Zard80 will wait for Serial to connect, and print `[Zard80] Online` to Serial. 

Z80 IO Port 0 is mapped to Serial I/O. When reading from port 0, a response of `0xFF` indicates that no character is
available to be read.

Zard80 will terminate and print debug events whenever:
 - The instruction `HALT` is executed on the Z80 (HALT pin is set to low.)
 - An instruction fetch, memory read, or memory write goes beyond the configured memory size.
 - An IO Read or Write is made to an unmapped port (i.e., any except for port zero.)

In these scenarios, the reason for termination will be printed, followed by all logged
debug events. The bottom-most debug event is typically the one that caused the termination.
