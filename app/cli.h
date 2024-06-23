#include <stdio.h>

typedef struct {
    char *rom_path;
} Arguments;

Arguments parse_run_args(int argc, char **argv);
