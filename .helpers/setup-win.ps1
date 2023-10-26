param([switch]$Elevated)

function Test-Admin {
    $currentUser = New-Object Security.Principal.WindowsPrincipal $([Security.Principal.WindowsIdentity]::GetCurrent())
    $currentUser.IsInRole([Security.Principal.WindowsBuiltinRole]::Administrator)
}

if ((Test-Admin) -eq $false)  {
    if ($elevated) {
        # tried to elevate, did not work, aborting
    } else {
        Start-Process powershell.exe -WorkingDirectory $PSScriptRoot -Verb RunAs -ArgumentList ('-noprofile -noexit -file "{0}" -elevated' -f ($myinvocation.MyCommand.Definition))
    }
    exit
}

'script obtained administrator privilege. continuing...'

$cs128env_dir=Convert-Path ../
docker run -d -v "${cs128env_dir}\src:/home/vagrant/src" -v "${cs128env_dir}\.shared:/home/vagrant/.shared" -v "${cs128env_dir}\.helpers:/home/vagrant/.helpers" -p 127.0.0.1:2222:22 --security-opt seccomp=unconfined --cap-add=SYS_PTRACE --name cs128env michaelrnowak/cpp-dev-env:latest
