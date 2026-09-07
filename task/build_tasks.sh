#!/bin/bash
set -euo pipefail

CC=${CC:-riscv64-unknown-elf-gcc}
OBJCOPY=${OBJCOPY:-riscv64-unknown-elf-objcopy}

CFLAGS=(
  -march=rv32ima
  -mabi=ilp32
  -nostdlib
  -nostartfiles
  -nodefaultlibs
  -fPIC
  -Wl,-e,_start
  -Wl,-Ttext=0x0
)

build_one() {
  local src="$1"
  local base="${src%.asm}"

  "$CC" "${CFLAGS[@]}" -x assembler-with-cpp "$src" -o "$base.elf"
  "$OBJCOPY" -O binary "$base.elf" "$base.bin"
  echo "Built: $base.bin"
}

build_one "$(dirname "$0")/child.asm"
build_one "$(dirname "$0")/hello.asm"
build_one "$(dirname "$0")/control.asm"
