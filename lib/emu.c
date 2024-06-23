#include <stdlib.h>
#include "emu.h"
#include "cart.h"

Cartridge cartridge = {};

void load_cartridge(char *path) {
    if (!read_cartridge(path, &cartridge)) {
        printf("Unable to open the file %s\n", path);
        exit(1);
    }
    if (!is_checksum_valid(&cartridge)) {
        printf("Calculated and expected cartridge checksums did not match.");
    }
    print_header(cartridge.header);
}

void run(char *rom_path) {
    load_cartridge(rom_path);
}
