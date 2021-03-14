param ([Parameter(
            Mandatory = $True,
            ValueFromRemainingArguments = $True,
            Position = 0,
            HelpMessage = "List of files to be signed (full file paths with no quotes, e.g. C:\Temp\Example.exe)")]
        [string[]]
        $Files)

$CodeSigningFolder = $PSScriptRoot

Set-Alias SignTool ($CodeSigningFolder + "\signtool.exe")
$CertificateFilePath = $CodeSigningFolder + "\PagoogInc.pfx"
$TimeStampServer = "http://timestamp.digicert.com"

Write-Host "Signing file(s)..."
Write-Host

$FailedSign = $False

foreach ($File in $Files)
{
    if (!(Test-Path -PathType leaf $File))
    {
        Write-Error "The file ""$File"" does not exist!"
        Write-Host

        $FailedSign = $True

        continue
    }

    Write-Host "Signing ""$File"""

    SignTool sign /v /f "$CertificateFilePath" /fd sha256 /tr "$TimeStampServer" /td sha256 /p Bigsambigsam1 "$File"
}

Write-Host "Finished signing files(s)"

if ($FailedSign -eq $True)
{
    exit 1
}               