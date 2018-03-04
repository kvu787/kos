if ($args.length -gt 0 -and $args -eq 'clean')
{
    rm *.o
    rm *.list
    rm *.img
    exit
}

$toolchainPrefix = 'gcc-arm-none-eabi-7-2017-q4-major-win32\bin\arm-none-eabi-'

& "$($toolchainPrefix)as" -march=armv6 kernel.s -o kernel.o
& "$($toolchainPrefix)objdump" -D kernel.o > kernel.o.list
& "$($toolchainPrefix)objcopy" kernel.o -O binary kernel.img
