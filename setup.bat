@echo off
set VCPKG_ROOT=%CD%\vcpkg
set TRIPLET=x64-windows-static
set LIBS=SDL3

if %TRIPLET%=="" set TRIPLET=x64-windows-static

echo Checking for vcpkg...
if not exist "%VCPKG_ROOT%" (
    echo Cloning vcpkg...
    git clone https://github.com/microsoft/vcpkg.git %VCPKG_ROOT%
    call %VCPKG_ROOT%\bootstrap-vcpkg.bat
    .\%VCPKG_ROOT%\vcpkg integrate install
) else (
    echo "Updating vcpkg...
    %VCPKG_ROOT%\ git pull
    %VCPKG_ROOT%\vcpkg.exe update
    %VCPKG_ROOT%\vcpkg.exe upgrade
)

echo Installing libraries: %LIBS%
%VCPKG_ROOT%\vcpkg.exe install %LIBS% --triplet %TRIPLET%

echo libs installed installed!
