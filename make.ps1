if ($args.length -gt 0 -and $args -eq 'clean')
{
    rm *.o
    rm *.list
    rm *.img
    rm *.elf
    exit
}

$toolchainPrefix = 'gcc-arm-none-eabi-7-2017-q4-major-win32\bin\arm-none-eabi-'

& "$($toolchainPrefix)gcc" -ffreestanding -c -march=armv6 *.s *.c
& "$($toolchainPrefix)ld" -T link.ld -o kernel.elf *.o
& "$($toolchainPrefix)objdump" -D kernel.elf > kernel.elf.list
& "$($toolchainPrefix)objcopy" -O binary kernel.elf kernel.img
