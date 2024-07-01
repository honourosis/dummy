#include "mem.h"
#include "cart.h"
#include "ram.h"

/**
 * 0000 - 3FFF  16 KiB ROM bank 00 From cartridge, usually a fixed bank
 * 4000 - 7FFF  16 KiB ROM Bank 01–NN From cartridge, switchable bank via mapper (if any)
 * 8000 - 9FFF  8 KiB Video RAM (VRAM) In CGB mode, switchable bank 0/1
 * A000 - BFFF  8 KiB External RAM	From cartridge, switchable bank if any
 * C000 - CFFF  4 KiB Work RAM (WRAM)
 * D000 - DFFF  4 KiB Work RAM (WRAM) In CGB mode, switchable bank 1–7
 * E000 - FDFF  Echo RAM (mirror of C000–DDFF). Use of this area is prohibited.
 * FE00 - FE9F  Object attribute memory (OAM)
 * FEA0 - FEFF  Not Usable. Use of this area is prohibited.
 * FF00 - FF7F  I/O Registers
 * FF80 - FFFE  High RAM (HRAM)
 * FFFF - FFFF  Interrupt Enable register (IE)
*/

uint8_t read_mem(uint16_t pointer) {
    if (pointer < 0x8000) {
        return lookup_card_data(pointer);
    }
    if (is_ram(pointer)) {
        return lookup_ram_data(pointer);
    }
    printf("Incorrect memory address %x. Normal mapping will be implemented later :(", pointer);
    exit(1);
}

uint8_t write_mem(uint16_t pointer, uint8_t value) {
    if (pointer < 0x8000) {
        write_card_data(pointer, value);
    } else if (is_ram(pointer)) {
        write_ram_data(pointer, value);
    } else {
        printf("Incorrect memory address %x. Normal mapping will be implemented later :(", pointer);
        exit(1);
    }
}