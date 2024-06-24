#pragma once

#include "common.h"

typedef struct {
    uint8_t entry[4];
    uint8_t logo[48];
    uint8_t title[16];
    uint16_t new_license_code;
    uint8_t sgb_flag;
    uint8_t type;
    uint8_t rom_size;
    uint8_t ram_size;
    uint8_t destination_code;
    uint8_t lic_code;
    uint8_t version;
    uint8_t header_checksum;
    uint16_t global_checksum;
} Header;

typedef struct {
    size_t rom_size;
    uint8_t *rom;
    Header *header;
} Cartridge;

bool read_cartridge(char *romPath);

void print_header(Header *header);

uint8_t lookup_card_data(uint16_t address);

