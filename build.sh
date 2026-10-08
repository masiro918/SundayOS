#!/bin/bash
make
riscv64-unknown-elf-objcopy -O binary kernel.elf kernel.bin

# run

sudo python3 ../SundayRISC/emulator.py kernel.bin
#cd ../SundayRISC/new_implementation/
#python3 emulator.py kernel.bin