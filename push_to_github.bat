@echo off
chcp 65001 >nul
setlocal enabledelayedexpansion
cd /d %~dp0

title Day code va Build APK len GitHub (NKSuyTinh)

call "%~dp0build_and_push_github.bat"
