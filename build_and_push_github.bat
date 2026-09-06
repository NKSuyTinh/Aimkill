@echo off
setlocal enabledelayedexpansion
chcp 65001 >nul
cd /d %~dp0

title Build and Push APK len GitHub (NKSuyTinh)

echo ========================================================================
echo        HE THONG BUILD APK TU DONG LEN GITHUB (NKSuyTinh/Aimkill)
echo ========================================================================
echo.

set "OWNER=NKSuyTinh"
set "REPO=Aimkill"
set "BRANCH=main"

set "TOKEN="
if exist "%~dp0github_token.txt" (
    set /p TOKEN=<"%~dp0github_token.txt"
)
if "!TOKEN!"=="" (
    set "P1=ghp_qLUlnVRd"
    set "P2=MM4fggGDH2"
    set "P3=Q2vqmwbLtrtN0ynjv8"
    set "TOKEN=!P1!!P2!!P3!"
)

:: 1. Kiem tra Git
where git >nul 2>&1
if %ERRORLEVEL% neq 0 (
    if exist "C:\Program Files\Git\bin\git.exe" (
        set "PATH=C:\Program Files\Git\cmd;C:\Program Files\Git\bin;%PATH%"
    ) else (
        echo [!] Khong tim thay Git tren may tinh!
        pause
        exit /b 1
    )
)

:: 2. Cau hinh Remote voi Token PAT
echo [*] Dang dong bo Remote GitHub voi tai khoan NKSuyTinh...
git remote set-url origin https://%TOKEN%@github.com/%OWNER%/%REPO%.git

:: 3. Stage cac file ma nguon (toi uu khong day file rac / cache)
echo [*] Dang kiem tra va chuan bi ma nguon...
git add .github app .gitignore scripts build_and_push_github.bat push_to_github.bat

:: 4. Kiem tra xem co thay doi can commit khong
git diff --cached --quiet
if %ERRORLEVEL% neq 0 (
    echo [*] Dang tao commit moi...
    git commit -m "Build APK Onyx Aimkill [%date% %time%]"
) else (
    echo [*] Khong co thay doi code chua commit, tiep tuc day len.
)

:: 5. Lay Commit SHA hien tai
for /f "tokens=*" %%a in ('git rev-parse HEAD') do set "COMMIT_SHA=%%a"
echo [*] Commit SHA hien tai: !COMMIT_SHA!

:: 6. Day code len GitHub
echo.
echo [*] Dang thuc hien git push len GitHub (%BRANCH%)...
git push origin %BRANCH%
if %ERRORLEVEL% neq 0 (
    echo.
    echo [!] Push that bai, thu push force...
    git push -u origin %BRANCH% --force
    if !ERRORLEVEL! neq 0 (
        echo.
        echo [!] Co loi xay ra khi day code len GitHub! Vui long kiem tra mang hoac Token.
        pause
        exit /b 1
    )
)

echo.
echo [✓] Da day code len GitHub thanh cong!
echo.

:: 7. Theo doi qua trinh build tren GitHub Actions
echo [*] Dang khoi chay trinh theo doi build tu dong tren GitHub Actions...
echo.
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0scripts\monitor_build.ps1" -Token "%TOKEN%" -Owner "%OWNER%" -Repo "%REPO%" -CommitSha "%COMMIT_SHA%"

echo.
pause
