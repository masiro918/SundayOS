CC = riscv64-unknown-elf-gcc
QEMU = qemu-system-riscv32
QFLAGS = -nographic -smp 4 -machine virt -bios none
OBJDUMP = riscv64-unknown-elf-objdump
TARGET = kernel.elf

CFLAGS = -nostdlib -fno-builtin -mcmodel=medany -march=rv32ima -mabi=ilp32 -Iinclude

C_SRCS = $(wildcard *.c) $(wildcard drivers/*.c) $(wildcard kernel/*.c) $(wildcard lib/*.c) $(wildcard tasks/*.c)
S_SRCS = $(wildcard boot/*.s) $(wildcard drivers/*.s) $(wildcard kernel/*.s) $(wildcard lib/*.s)  

C_OBJ = $(C_SRCS:.c=.o)
S_OBJ = $(S_SRCS:.s=.s.o)
OBJ = boot/start.s.o $(filter-out boot/start.s.o,$(S_OBJ)) $(C_OBJ)

all: kernel.elf

kernel.elf: clean $(OBJ)
	$(CC) $(CFLAGS) -T os.ld -o kernel.elf $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.s.o: %.s
	$(CC) $(CFLAGS) -c $< -o $@

qemu: $(TARGET)
	@qemu-system-riscv32 -M ? | grep virt >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit QEMU"
	$(QEMU) $(QFLAGS) -kernel kernel.elf

disasm: $(TARGET)
	$(OBJDUMP) -d $(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all qemu clean disasm
