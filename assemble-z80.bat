zasm main.z80 --reqcolon
echo #include "z80mem.h" > src/z80mem.cpp
echo uint8_t ZMem::memory[MEMORY_MAX] { >> src/z80mem.cpp
type main.rom | xxd -i>> src/z80mem.cpp
echo }; >> src/z80mem.cpp
