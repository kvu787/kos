$toolchainPath = 'gcc-arm-none-eabi-7-2017-q4-major-win32\bin'
foreach ($file in Get-ChildItem $toolchainPath)
{
    if ($file.Name.StartsWith('arm-none-eabi-'))
    {
        $file.Name.Split(".")[0].Split("-")[-1]
        $file.FullName
        Set-Alias -Name $file.Name.Split(".")[0].Split("-")[-1] -Value $file.FullName -Scope Global
    }
}
