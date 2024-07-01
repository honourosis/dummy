#pragma once

#include "common.h"

typedef struct {
    uint8_t wram[0x2000];
    uint8_t hram[0x80];
} Ram;

uint8_t lookup_ram_data(uint16_t address);

void write_ram_data(uint16_t address, uint8_t value);

bool is_ram(uint16_t address);