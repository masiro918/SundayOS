# Mini Kernel

A very small demonstrative operating system kernel for **SundayRISC emulator** [1]. Inspired by mini-riscv-os [2].

## What it includes
- Basic boot/link setup for bare-metal execution
- Simple task creation and context switching
- Round-robin scheduler
- Timer interrupt initialization
- Minimal stdlib/stdio-style support and sample user tasks

## Project layout
- `boot/` – startup assembly
- `kernel/` – scheduler, task/context, memory/task management
- `drivers/` – interrupt and screen/console-related code
- `tasks/` – demo tasks run by the scheduler
- `stdlib/`, `include/` – lightweight runtime and headers

## Build and run

You need SundayRISC emulator to run this program.

```bash
./build.sh
```

Useful extras:
```bash
make disasm
make clean
```

## References

[1] https://github.com/masiro918/SundayRISC

[2] https://github.com/manbing/mini-riscv-os
