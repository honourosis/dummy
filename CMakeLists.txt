cmake_minimum_required(VERSION 3.28)
project(dummy C)

set(CMAKE_C_STANDARD 11)

add_executable(dummy app/main.c
        app/cli.c
        app/cli.h
        lib/emu.c
        lib/emu.h
        lib/cart.c
        lib/cart.h
        lib/cpu.h
)
