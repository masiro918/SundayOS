#include "types.h"

#define MMIO_BASE        0x200000
#define ADDR_SCREEN_DATA (MMIO_BASE + 0x0)

extern void poke(uint32_t addr, uint8_t val);


/**
 * Prints char to screen through MMIO.
 */
uint8_t putc(char c) {
    poke(ADDR_SCREEN_DATA, (uint8_t)c);
    return (uint8_t)c;
}