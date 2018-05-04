ARM_TOOLCHAIN = gcc-arm-none-eabi-7-2017-q4-major-win32/bin/arm-none-eabi

CC = $(ARM_TOOLCHAIN)-gcc
LD = $(ARM_TOOLCHAIN)-ld
OBJDUMP = $(ARM_TOOLCHAIN)-objdump
OBJCOPY = $(ARM_TOOLCHAIN)-objcopy

CFLAGS = -O0 -Wpedantic -Wall -std=c11 -ffreestanding -c -march=armv6
LDFLAGS = -L'gcc-arm-none-eabi-7-2017-q4-major-win32/arm-none-eabi/lib' -l'c'

kernel: src/*.s src/*.c src/test/*.c
	# Compile object files
	$(CC) $(CFLAGS) $^
	# Link object files
	$(LD) -T link.ld -o kernel.elf *.o $(LDFLAGS)
	# Dump kernel binary
	$(OBJDUMP) -D kernel.elf > kernel.elf.list
	# Generate raw binary
	$(OBJCOPY) -O binary kernel.elf kernel.img

clean:
	rm -f *.o *.elf *.list *.img
