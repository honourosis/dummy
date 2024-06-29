#include "common.h"

uint16_t join_8b_16b(uint8_t lo, uint8_t hi) {
    return lo | (hi << 8);
}

void log_verbose(char *str) {
    if (LOG_VERBOSE) {
        printf("Log: %s", str);
    }
}

uint16_t swap_int16(uint16_t val) {
    return (val << 8) | ((val >> 8) & 0xFF);
}