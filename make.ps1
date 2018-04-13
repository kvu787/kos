function Clean {
    rm *.o
    rm *.list
    rm *.img
    rm *.elf
}

if ($args.length -gt 0 -and $args[0] -eq 'clean')
{
    Clean
    exit
}

$toolchainPrefix = 'gcc-arm-none-eabi-7-2017-q4-major-win32\bin\arm-none-eabi-'

Clean
# TODO: enable pointer-sign warning
& "$($toolchainPrefix)gcc" -Wno-pointer-sign -Wall -ffreestanding -c -march=armv6 *.s *.c
& "$($toolchainPrefix)ld" -L'gcc-arm-none-eabi-7-2017-q4-major-win32/arm-none-eabi/lib' -T link.ld -o kernel.elf *.o -l'c'
& "$($toolchainPrefix)objdump" -D kernel.elf > kernel.elf.list
& "$($toolchainPrefix)objcopy" -O binary kernel.elf kernel.img
