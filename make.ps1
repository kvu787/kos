if ($args.length -gt 0 -and $args -eq 'clean')
{
    rm *.o
    rm *.list
    rm *.img
    rm *.elf
    exit
}

$toolchainPrefix = 'gcc-arm-none-eabi-7-2017-q4-major-win32\bin\arm-none-eabi-'

& "$($toolchainPrefix)as" -march=armv6 kernel.s -o kernel.o
& "$($toolchainPrefix)ld" kernel.o -T link.ld -o kernel.elf
& "$($toolchainPrefix)objdump" -D kernel.elf > kernel.elf.list
& "$($toolchainPrefix)objcopy" kernel.elf -O binary kernel.img
