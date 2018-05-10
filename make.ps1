$toolchainPrefix = 'gcc-arm-none-eabi-7-2017-q4-major-win32\bin\arm-none-eabi-'
Set-Alias -Name cc -Value "$($toolchainPrefix)gcc"
Set-Alias -Name ld -Value "$($toolchainPrefix)ld"
Set-Alias -Name objdump -Value "$($toolchainPrefix)objdump"
Set-Alias -Name objcopy -Value "$($toolchainPrefix)objcopy"

function Main {
    switch ($args[0]) {
        'kernel' {
            Build-Kernel
            break
        }
        'sd' {
            Build-Kernel
            $imagePath = "obj\kernel.img"
            $drivePath = (wmic logicaldisk where "VolumeName='KOS'" get Caption 2>$null)[2]
            if ($drivePath.length -eq 0) {
                throw 'No drive with label=KOS was found.'
                exit
            }
            $drivePath = $drivePath.trim()
            cp $imagePath $drivePath\kernel.img
            break
        }
        'clean' {
            Clean-ObjectDirectory
            break
        }
    }
}

function Build-Kernel {
    $srcDir = 'src'
    $objDir = 'obj'
    if (Test-Path $objDir) {
        Remove-Item -Force -Recurse -Path $objDir
    }
    mkdir $objDir > $null
    cc -O0 -Wpedantic -Wall -ffreestanding -c -march=armv6 -std=c11 $srcDir\*.s $srcDir\*.c $srcDir\test\*.c
    mv *.o $objDir
    ld -L'gcc-arm-none-eabi-7-2017-q4-major-win32/arm-none-eabi/lib' -T link.ld -o $objDir\kernel.elf $objDir\*.o -l'c'
    objdump -D $objDir\kernel.elf > $objDir\kernel.elf.list
    objcopy -O binary $objDir\kernel.elf $objDir\kernel.img
}

function Clean-ObjectDirectory {
    if (Test-Path obj) {
        Remove-Item -Force -Recurse -Path obj
    }
}

Main($args)
