OUTPUT_ARCH(riscv)
ENTRY(_start)

MEMORY
{
    RAM (rwx) : ORIGIN = 0x10074, LENGTH = 128M
}

SECTIONS
{
    . = ORIGIN(RAM);

    .text.boot : ALIGN(4)
    {
        KEEP(*(.text.boot))
    } > RAM

    .trapvec 0x10274 :
    {
        KEEP(*(.trapvec))
    } > RAM

    .text : ALIGN(4)
    {
        *(.text .text.*)
    } > RAM

    .rodata : ALIGN(4)
    {
        *(.rodata .rodata.*)
    } > RAM

    .data : ALIGN(4)
    {
        *(.data .data.*)
    } > RAM

    .bss (NOLOAD) : ALIGN(4)
    {
        __bss_start = .;
        *(.bss .bss.*)
        *(COMMON)
        __bss_end = .;
    } > RAM

    . = ALIGN(16);
    __end = .;
    _end = .;

    /DISCARD/ :
    {
        *(.comment)
        *(.note*)
        *(.eh_frame*)
        *(.gnu*)
    }
}
