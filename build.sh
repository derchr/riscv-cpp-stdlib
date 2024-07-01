riscv64-unknown-elf-g++ -o main.elf -nostdlib -nostartfiles -fno-exceptions -fno-unwind-tables -fno-rtti -T linker.ld start.S trap.c main.cpp uart.c -lstdc++ -lc -lgcc -mcmodel=medany
