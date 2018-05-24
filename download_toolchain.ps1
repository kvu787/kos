'Downloading ZIP file for ARM GCC toolchain...'
Invoke-WebRequest -Uri 'https://developer.arm.com/-/media/Files/downloads/gnu-rm/7-2017q4/gcc-arm-none-eabi-7-2017-q4-major-win32.zip?revision=df1b65d3-7c8d-4e82-b114-e0b6ad7c2e6d?product=GNU%20Arm%20Embedded%20Toolchain,ZIP,,Windows,7-2017-q4-major' -OutFile 'gcc-arm-none-eabi-7-2017-q4-major-win32.zip'

'Checking ZIP file MD5 signature...'
$hash = (Get-FileHash 'gcc-arm-none-eabi-7-2017-q4-major-win32.zip' -Algorithm MD5).Hash
if ($hash -ne '168c68c41ee0986ecc1dadceaa8b6a3f')
{
  "You've downloaded a corrupted file. Exiting..."
  exit
}

'Expanding ZIP file...'
Expand-Archive 'gcc-arm-none-eabi-7-2017-q4-major-win32.zip'

'Deleting ZIP file...'
Remove-Item 'gcc-arm-none-eabi-7-2017-q4-major-win32.zip'

'Downloading ZIP file for TeraTerm toolchain...'
Invoke-WebRequest -Uri 'https://osdn.net/frs/redir.php?m=pumath&f=ttssh2%2F69111%2Fteraterm-4.98.zip' -OutFile 'teraterm-4.98.zip'

'Checking ZIP file SHA256 signature...'
$hash = (Get-FileHash 'teraterm-4.98.zip' -Algorithm SHA256).Hash
if ($hash -ne 'bfa9bf284a9bbc1c93e3fd2498a36be2ec05ece2df7d487fc54f68cb745f578f')
{
  "You've downloaded a corrupted file. Exiting..."
  exit
}

'Expanding ZIP file...'
Expand-Archive 'teraterm-4.98.zip'

'Deleting ZIP file...'
Remove-Item 'teraterm-4.98.zip'
