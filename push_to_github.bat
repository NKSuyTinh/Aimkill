@echo off
setlocal
cd /d %~dp0
set PATH=C:\Program Files\Git\cmd;C:\Program Files\Git\bin;C:\Program Files\Git\mingw64\bin;%PATH%
title Day code len GitHub

echo ========================================================
echo         DANG DAY DU AN LEN GITHUB (NKSuyTinh/Aimkill)
echo ========================================================
echo.
echo [*] Chu y: Neu trinh duyet bat len cua so GitHub,
echo     hay bam "Sign in with your browser" hoac "Authorize"!
echo.
echo [*] Dang thuc hien git push...
echo.

"C:\Program Files\Git\bin\git.exe" push -u origin main --force

if %ERRORLEVEL% equ 0 (
    echo.
    echo ========================================================
    echo  [THANH CONG] Toan bo code da duoc day len GitHub!
    echo  GitHub Actions dang tu dong build file APK cho ban.
    echo ========================================================
    echo.
    echo [*] Dang mo trang GitHub Actions de ban theo doi...
    start https://github.com/NKSuyTinh/Aimkill/actions
) else (
    echo.
    echo [!] Co loi xay ra trong qua trinh day code.
)
echo.
pause
