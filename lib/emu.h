#pragma once

#include "common.h"

typedef struct {
    bool running;
} State;

void run(char *rom_path);