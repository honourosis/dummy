#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define TODO exit(1); printf("Will be implemented later");

uint16_t join_8b_16b(uint8_t lo, uint8_t hi);
