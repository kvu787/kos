$toolchainPrefix = 'gcc-arm-none-eabi-7-2017-q4-major-win32\bin\arm-none-eabi-'
Set-Alias -Name cc -Value "$($toolchainPrefix)gcc"
Set-Alias -Name ld -Value "$($toolchainPrefix)ld"
Set-Alias -Name objdump -Value "$($toolchainPrefix)objdump"
Set-Alias -Name objcopy -Value "$($toolchainPrefix)objcopy"

function Main {
    switch ($args[0]) {
        'boot' {
            Build-Kernel
            Build-Sender
            Foreach ($entry in (change port)) {
                if ($entry.Contains('ProlificSerial')) {
                    $port = [Regex]::Match($entry, 'COM(\d+)').Groups[1].Value
                }
            }
            if ($port -eq $null) {
                throw 'No COM port name contains ProlificSerial'
            }
            obj\sender\sender.exe COM$port obj\kernel\kernel.img
            .\teraterm-4.98\teraterm-4.98\ttermpro.exe /BAUD=115200 /C=$port
            break
        }
        'sd' {
            Build-Bootloader
            $imagePath = "obj\bootloader\bootloader.img"
            $drivePath = (wmic logicaldisk where "VolumeName='KOS'" get Caption 2>$null)[2]
            if ($drivePath.Length -eq 0) {
                throw 'No drive with label=KOS was found.'
                exit
            }
            $drivePath = $drivePath.Trim()
            cp $imagePath $drivePath\kernel.img
            break
        }
        'kernel' {
            Build-Kernel
            break
        }
        'bootloader' {
            Build-Bootloader
            break
        }
        'sender' {
            Build-Sender
            break
        }
        'clean' {
            Clean-ObjectDirectory
            break
        }
    }
}

function Build-Kernel {
    $srcDir = 'src\kernel'
    $objDir = 'obj\kernel'
    if (Test-Path $objDir) {
        Remove-Item -Force -Recurse -Path $objDir
    }
    mkdir $objDir > $null
    cc -O0 -Wpedantic -Wall -ffreestanding -c -march=armv6 -std=c11 $srcDir\*.s $srcDir\*.c $srcDir\test\*.c
    mv *.o $objDir
    ld -L'gcc-arm-none-eabi-7-2017-q4-major-win32/arm-none-eabi/lib' -T $srcDir\link.ld -o $objDir\kernel.elf $objDir\*.o -l'c'
    objdump -D $objDir\kernel.elf > $objDir\kernel.elf.list
    objcopy -O binary $objDir\kernel.elf $objDir\kernel.img
}

function Build-Bootloader {
    $srcDir = 'src\bootloader'
    $objDir = 'obj\bootloader'
    if (Test-Path $objDir) {
        Remove-Item -Force -Recurse -Path $objDir
    }
    mkdir $objDir > $null
    cc -O0 -Wpedantic -Wall -ffreestanding -c -march=armv6 -std=gnu11 $srcDir\*.s $srcDir\*.c
    mv *.o $objDir
    ld -T $srcDir\link.ld -o $objDir\bootloader.elf $objDir\*.o
    objdump -D $objDir\bootloader.elf > $objDir\bootloader.elf.list
    objcopy -O binary $objDir\bootloader.elf $objDir\bootloader.img
    $bootloaderSize = (Get-ChildItem $objDir\bootloader.img).Length
    $bootloaderMaxSize = 0x1000
    if ($bootloaderSize -gt $bootloaderMaxSize) {
        throw "Bootloader is $bootloaderSize bytes, but must be <= $bootloaderMaxSize bytes"
    }
}

function Build-Sender {
    & 'C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin\MSBuild.exe' src\sender\sender.sln `
        '/p:OutDir=..\..\..\obj\sender\;IntDir=..\..\..\obj\sender\;Configuration=Release;Platform=x64'
}

function Clean-ObjectDirectory {
    if (Test-Path obj) {
        Remove-Item -Force -Recurse -Path obj
    }
}

Main($args)
