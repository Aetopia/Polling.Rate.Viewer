@echo off
cd "%~dp0">nul 2>&1
rmdir /Q /S "bin">nul 2>&1
mkdir "bin">nul 2>&1

gcc.exe -Os -Wl,--gc-sections -nostdlib -s "WinMain.c" -lKernel32 -lUser32 -o "bin\Polling.Rate.Viewer.exe"

upx.exe --best --ultra-brute "bin\*">nul 2>&1