(You'll probably need to run something like "Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass" so you can run the following PowerShell scripts.)

Run download_toolchain.ps1 to download the toolchain.
Run make.ps1 to compile kernel.img.
Run "make.ps1 clean" to clean up object files.
