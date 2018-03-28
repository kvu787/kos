$toolchainPath = 'gcc-arm-none-eabi-7-2017-q4-major-win32\bin'
foreach ($file in Get-ChildItem $toolchainPath)
{
    if ($file.Name.StartsWith('arm-none-eabi-'))
    {
        $command = $file.Name.Substring('arm-none-eabi-'.Length).Split(".")[0]
        Set-Alias -Name $command -Value $file.FullName -Scope Global
    }
}
