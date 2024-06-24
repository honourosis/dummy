#include "mem.h"
#include "cart.h"

uint8_t read_mem(uint16_t pointer) {
    if (pointer < 0x8000) {
        return lookup_card_data(pointer);
    }
    printf("Incorrect memory address %x. Normal mapping will be implemented later :(", pointer);
    exit(1);
}