#include <stdio.h>
#include "cli.h"
#include "../lib/emu.h"

int main(int argc, char **argv) {
    Arguments arguments = parse_run_args(argc, argv);
    run(arguments.rom_path);
}