#include "ram.h"

Ram ram = {};

uint8_t lookup_ram_data(uint16_t address) {
    if (address > 0xC000 && address <= 0xCFFF) {
        return ram.wram[address - 0xC000];
    }
    if (address > 0xFF80 && address <= 0xFFFE) {
        return ram.hram[address - 0xFF80];
    }
    TODO
}

void write_ram_data(uint16_t address, uint8_t value) {
    if (address > 0xC000 && address <= 0xCFFF) {
        ram.wram[address - 0xC000] = value;
    }
    if (address > 0xFF80 && address <= 0xFFFE) {
        ram.hram[address - 0xFF80] = value;
    }
}

bool is_ram(uint16_t address) {
    return (address > 0xC000 && address <= 0xCFFF) || (address > 0xFF80 && address <= 0xFFFE);
}
