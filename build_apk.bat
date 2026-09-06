@echo off
setlocal
cd /d "%~dp0"

:: Map virtual drive X: to bypass space issues in NDK path
subst X: /d >nul 2>&1
subst X: "%~dp0" >nul 2>&1
if exist X:\ (
    cd /d X:\
)

set "JAVA_HOME=C:\Program Files\Android\Android Studio\jre"
if not exist "%JAVA_HOME%\bin\java.exe" (
    set "JAVA_HOME=C:\Program Files\Android\jdk\jdk-8.0.302.8-hotspot\jdk8u302-b08"
)
set PATH=%JAVA_HOME%\bin;%PATH%
title Onyx APK Builder

:menu
cls
echo ========================================
echo        ONYX APK BUILD SYSTEM
echo ========================================
echo.
echo [1] Build Debug APK (Standard)
echo [2] Build Release APK (Optimized)
echo [3] Clean Project (Fix Errors)
echo [4] Exit
echo.
set /p choice="Enter choice (1-4): "

if "%choice%"=="1" goto debug
if "%choice%"=="2" goto release
if "%choice%"=="3" goto clean
if "%choice%"=="4" goto end

:debug
echo.
echo [*] Building Debug APK...
call gradlew.bat assembleDebug
if %ERRORLEVEL% equ 0 (
    echo.
    echo [!] Build SUCCESSFUL!
    echo [*] Opening output folder...
    start "" "app\build\outputs\apk\debug\"
) else (
    echo.
    echo [X] Build FAILED! Please check the logs above.
)
pause
goto menu

:release
echo.
echo [*] Building Release APK...
call gradlew.bat assembleRelease
if %ERRORLEVEL% equ 0 (
    echo.
    echo [!] Build SUCCESSFUL!
    echo [*] Opening output folder...
    start "" "app\build\outputs\apk\release\"
) else (
    echo.
    echo [X] Build FAILED! Please check the logs above.
)
pause
goto menu

:clean
echo.
echo [*] Cleaning project...
call gradlew.bat clean
echo.
echo [!] Clean complete.
pause
goto menu

:end
exit
