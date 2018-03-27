'Downloading ZIP file for ARM GCC toolchain...'
Invoke-WebRequest -Uri 'https://developer.arm.com/-/media/Files/downloads/gnu-rm/7-2017q4/gcc-arm-none-eabi-7-2017-q4-major-win32.zip?revision=df1b65d3-7c8d-4e82-b114-e0b6ad7c2e6d?product=GNU%20Arm%20Embedded%20Toolchain,ZIP,,Windows,7-2017-q4-major' -OutFile 'gcc-arm-none-eabi-7-2017-q4-major-win32.zip'

'Checking ZIP file MD5 signature...'
$md5Hash = (Get-FileHash 'gcc-arm-none-eabi-7-2017-q4-major-win32.zip' -Algorithm MD5).Hash
if ($md5Hash -ne '168c68c41ee0986ecc1dadceaa8b6a3f')
{
  "You've downloaded a corrupted file. Exiting..."
  exit  
}

'Expanding ZIP file...'
Expand-Archive 'gcc-arm-none-eabi-7-2017-q4-major-win32.zip'

'Deleting ZIP file...'
Remove-Item 'gcc-arm-none-eabi-7-2017-q4-major-win32.zip'
