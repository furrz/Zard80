#include "z80mem.h" 
uint8_t ZMem::memory[MEMORY_MAX] { 
  0x31, 0x00, 0x10, 0x21, 0x20, 0x00, 0xcd, 0x19, 0x00, 0xdb, 0x00, 0xfe,
  0xff, 0x30, 0xfa, 0x21, 0x31, 0x00, 0xcd, 0x19, 0x00, 0xf3, 0x76, 0xd3,
  0x00, 0x7e, 0x23, 0xfe, 0x00, 0x20, 0xf8, 0xc9, 0x50, 0x72, 0x65, 0x73,
  0x73, 0x20, 0x61, 0x6e, 0x79, 0x20, 0x6b, 0x65, 0x79, 0x21, 0x5c, 0x6e,
  0x00, 0x54, 0x68, 0x61, 0x74, 0x20, 0x77, 0x61, 0x73, 0x6e, 0x27, 0x74,
  0x20, 0x74, 0x68, 0x65, 0x20, 0x41, 0x6e, 0x79, 0x20, 0x6b, 0x65, 0x79,
  0x21, 0x5c, 0x6e, 0x00
}; 
