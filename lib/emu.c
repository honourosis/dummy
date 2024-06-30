#include "emu.h"
#include "cpu.h"
#include "cart.h"

State state = {true};

void run(char *rom_path) {
    read_cartridge(rom_path);
    init_cpu();
    while (state.running) {
        cpu_step();
    }
}
