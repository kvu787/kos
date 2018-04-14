function Clean {
    Remove-Item -Force -Recurse -Path obj
}

if ($args.length -gt 0 -and $args[0] -eq 'clean')
{
    Clean
    exit
}

$toolchainPrefix = 'gcc-arm-none-eabi-7-2017-q4-major-win32\bin\arm-none-eabi-'

Clean
mkdir obj > $null
& "$($toolchainPrefix)gcc" -O0 -Wpedantic -Wall -std=c11 -ffreestanding -c -march=armv6 src\*.s src\*.c src\test\*.c
mv *.o obj
& "$($toolchainPrefix)ld" -L'gcc-arm-none-eabi-7-2017-q4-major-win32/arm-none-eabi/lib' -T link.ld -o obj\kernel.elf obj\*.o -l'c'
& "$($toolchainPrefix)objdump" -D obj\kernel.elf > obj\kernel.elf.list
& "$($toolchainPrefix)objcopy" -O binary obj\kernel.elf obj\kernel.img
