#include "common.h"

uint16_t join_8b_16b(uint8_t lo, uint8_t hi) {
    return lo | (hi << 8);
}
