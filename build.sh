riscv64-unknown-elf-g++ -o main.elf -nostdlib -nostartfiles -fno-exceptions -fno-unwind-tables -fno-rtti -T linker.ld start.S trap.cpp syscall.cpp main.cpp uart.cpp -lstdc++ -lc -lgcc -mcmodel=medany
