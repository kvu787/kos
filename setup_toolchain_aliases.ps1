$toolchainPath = 'gcc-arm-none-eabi-7-2017-q4-major-win32\bin'
foreach ($file in Get-ChildItem $toolchainPath)
{
    if ($file.Name.StartsWith('arm-none-eabi-'))
    {
        $command = $file.Name.Split(".")[0].Split("-")[-1]
        Set-Alias -Name $command -Value $file.FullName -Scope Global
    }
}
