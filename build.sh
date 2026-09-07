#!/bin/bash
make
riscv64-unknown-elf-objcopy -O binary kernel.elf kernel.bin

# run

python3 ../SundayRISC/emulator.py kernel.bin