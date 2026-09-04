.global peek
/* uint8_t peek(uint32_t addr);  */
peek:
    lbu     a0, 0(a0)
    ret
.global peek32
/* uint8_t peek32(uint32_t addr);  */
peek32:
    lw     a0, 0(a0)
    ret

.global poke
/* void poke(uint32_t addr, uint8_t val);  */
poke:
    sb      a1, 0(a0)
    ret
.global poke32
/* void poke32(uint32_t addr, uint32_t val);  */
poke32:
    sw      a1, 0(a0)
    ret
