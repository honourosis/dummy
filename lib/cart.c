#include "cart.h"

#define F_MODE_READONLY_BINARY "rb"
#define HEADER_START 0x100

Cartridge cartridge = {};

bool is_checksum_valid() {
    uint8_t checksum = 0;
    for (uint16_t address = 0x0134; address <= 0x014C; address++) {
        checksum = checksum - cartridge.rom[address] - 1;
    }
    return cartridge.header->header_checksum == checksum;
}

void print_header(Header *header) {
    printf("Title: %s\n", header->title);
    printf("Sgb flag: %x\n", header->sgb_flag);
    printf("Type: %x\n", header->type);
    printf("Ram size: %i\n", header->ram_size);
    printf("Rom size: %i\n", header->rom_size);
    printf("Destination code: %i\n", header->destination_code);
    printf("License code: %i\n", header->lic_code);
    printf("Version: %i\n", header->version);
    printf("Header checksum: %i\n", header->header_checksum);
    printf("Global checksum: %i\n", header->global_checksum);
}

bool read_cartridge(char *romPath) {
    FILE *file = fopen(romPath, F_MODE_READONLY_BINARY);
    if (file == NULL) {
        return false;
    }
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    void *rom = malloc(file_size);
    fread(rom, file_size, 1, file);

    if (ferror(file)) {
        fclose(file);
        return false;
    }
    fclose(file);

    cartridge.rom_size = file_size;
    cartridge.rom = rom;
    cartridge.header = (Header *) (cartridge.rom + HEADER_START);

    if (!is_checksum_valid()) {
        printf("Calculated and expected cartridge checksums did not match.");
        return false;
    }

    print_header(cartridge.header);
    return true;
}

uint8_t lookup_card_data(uint16_t address) {
    return cartridge.rom[address];
}

uint8_t write_card_data(uint16_t address, uint8_t value) {
    cartridge.rom[address] = value;
}