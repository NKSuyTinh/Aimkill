@echo off
setlocal

:: Set Android NDK Path
set NDK_PATH=C:\Users\Administrator\AppData\Local\Android\Sdk\ndk\26.1.10909125
set TOOLCHAIN=%NDK_PATH%\toolchains\llvm\prebuilt\windows-x86_64
set SYSROOT=%TOOLCHAIN%\sysroot
set TARGET=aarch64-linux-android
set API=21

:: Compiler Paths
set CC=%TOOLCHAIN%\bin\%TARGET%%API%-clang
set CXX=%TOOLCHAIN%\bin\%TARGET%%API%-clang++

:: Input / Output
set SRC_FILE=Server.cpp
set OUTPUT_LIB=libserver.so

:: Include Paths (Ensure Unity is included)
set INCLUDES=-I%SYSROOT%/usr/include -I./Tools/Includes -I./Unity -I./Widgets

:: Compile & Link
echo Building %OUTPUT_LIB% for arm64-v8a...
"%CXX%" -shared -fPIC -o %OUTPUT_LIB% %SRC_FILE% %INCLUDES% --sysroot=%SYSROOT% -landroid -llog
"%CXX%" -shared -fPIC -o %OUTPUT_LIB% %SRC_FILE% -DNO_UNITY %INCLUDES% --sysroot=%SYSROOT% -landroid -llog


if %ERRORLEVEL% neq 0 (
    echo Build failed!
    exit /b %ERRORLEVEL%
)

echo Build successful! Output: %OUTPUT_LIB%
exit /b 0
