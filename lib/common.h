#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define TODO exit(1); printf("Will be implemented later");
#define LOG_VERBOSE true

uint16_t join_8b_16b(uint8_t lo, uint8_t hi);

void log_verbose(char *str);

uint16_t swap_int16(uint16_t val);