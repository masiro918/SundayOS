#include "types.h"

extern uint32_t peek(uint32_t addr);

int key_pressed() {
    uint32_t val = peek32(0x200034);
    if (val != 0) return 1;
    return 0;
}