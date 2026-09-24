@echo off
setlocal

:: %~1 Means first parameter passed after the Debug call (Quotes removed^)^

:: === CONFIG ===
set ROOT = C:\Midnight

:: === ARG CHECK ===
if "%~1"=="" (
    echo This .bat uses a filename as input to open along visual studio to make debugging and setting breakpoints easier (!!!NO _DebugBreak(^)^ PLEASE!!!^)
    echo You can call Debug with FileName.cpp or just FileName
    echo Example 1: Debug main.cpp
    echo Example 2: Deubg main  
    echo Usage: Debug ^<file-name^>
    exit /b 1
)

set FILENAME=%~1

:: Chek if file has .cpp. If not add it
echo %FILENAME% | findstr /i "\.cpp$" >nul
if errorlevel 1 (
    set FILENAME=%FILENAME%.cpp
)

set FILE_TO_OPEN =

:: === SEARCH FOR FILE ===
for /r %ROOT% %%f in (*%FILENAME%) do (
    set "FILE_TO_OPEN=%%f"
    goto :found
)

echo File "%FILENAME%" has been searched recursively and it hasn't been found inside any "%ROOT%" folder
goto :end

:found

devenv /debugexe C:\Midnight\bin\x64\Midnight.exe

:: === Wait for debugger to initialize ===
timeout /t 2 >nul

:: === Open the found source file ===
devenv /edit "%FILE_TO_OPEN%"

:end

endlocal
