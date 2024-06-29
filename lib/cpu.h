#include <stdint.h>

typedef struct {
    uint8_t A;
    uint8_t B;
    uint8_t C;
    uint8_t D;
    uint8_t E;
    uint8_t H;
    uint8_t L;
} Registers;

typedef struct {
    Registers registers;
    uint8_t stack_pointer;
    uint8_t program_counter;
} Cpu;
