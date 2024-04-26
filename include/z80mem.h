#pragma once
#include <stdint.h>

namespace ZMem {
    constexpr unsigned MEMORY_MAX = 4096;
    /// The Z80 memory buffer. This lives in src/z80mem.cpp, which is generated automatically when running z80build.
    extern uint8_t memory[MEMORY_MAX];

}