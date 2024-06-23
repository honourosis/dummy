#include <stdlib.h>
#include <string.h>
#include "cli.h"
#include "stdio.h"

Arguments parse_run_args(int argc, char **argv) {
    if (argc < 3) {
        printf("Not sufficient number of args.\n");
        printf("To run the program pass the '-r' argument with the path to the ROM file.\n");
        exit(1);
    }
    Arguments args = {};
    if (strcmp("-r", argv[1]) == 0) {
        args.rom_path = argv[2];
    }
    return args;
}
