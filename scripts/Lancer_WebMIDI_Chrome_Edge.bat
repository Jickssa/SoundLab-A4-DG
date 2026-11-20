@echo off
setlocal
cd /d "%~dp0.."
where py >nul 2>nul
if errorlevel 1 (
  echo Python 3 is required and must be on PATH.
  pause
  exit /b 1
)
start "" http://localhost:8765/index.html
py -3 -m http.server 8765 --bind 127.0.0.1
