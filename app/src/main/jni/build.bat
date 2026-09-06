@echo off
setlocal

:: ========== YAHAN APNA NDK PATH DALO ==========
set "NDK_PATH=C:\Users\Krishu\AppData\Local\Android\Sdk\ndk\25.1.8937393"
:: =============================================

set TOOLCHAIN=%NDK_PATH%\toolchains\llvm\prebuilt\windows-x86_64
set SYSROOT=%TOOLCHAIN%\sysroot
set TARGET=armv7a-linux-androideabi
set API=21

:: ARMv7 (32-bit) - Free Fire ke liye
set CC=%TOOLCHAIN%\bin\%TARGET%%API%-clang
set CXX=%TOOLCHAIN%\bin\%TARGET%%API%-clang++

set SRC_FILE=backend.cpp
set OUTPUT_LIB=libPHXCORP.so

set INCLUDES=-I"%SYSROOT%/usr/include" -I"./Tools/Includes" -I"./Unity" -I"./Widgets" -I"./Tools/SOCKET" -I"./Hack" -I"./AutoUpdate" -I"./AutoUpdate/xdl/include" -I"./Tools/KittyMemory" -I"./Tools/KittyMemory/Deps/Keystone/includes" -I"./Tools/And64InlineHook" -I"./Tools/Substrate" -I"./Tools/DrawTools" -I"./Tools/Canvas"

echo Building %OUTPUT_LIB% for armeabi-v7a...
"%CXX%" -shared -fPIC -o %OUTPUT_LIB% %SRC_FILE% %INCLUDES% -static-libstdc++ -llog -landroid -lGLESv2 --sysroot="%SYSROOT%"

if %ERRORLEVEL% neq 0 (
    echo Build failed!
    pause
    exit /b %ERRORLEVEL%
)

echo Build successful! Output: %OUTPUT_LIB%
pause
exit /b 0