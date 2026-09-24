@echo off

:ChooseNumber
echo.
echo #=================================#
echo ^|       Emacs Configuration       ^|
echo +=================================+
echo ^| 1. Open Emacs                   ^|
echo ^| 2. Open Emacs Init File         ^|
echo ^| 3. Open Emacs Folder            ^|
echo ^| 4. Exit                         ^|
echo #=================================#
echo.
set /p choice="Enter your choice: "

if "%choice%"=="1" goto openEmacs
if "%choice%"=="2" goto openEmacsInit
if "%choice%"=="3" goto openEmacsFolder
if "%choice%"=="4" goto end

echo.
echo !=================================!
echo ^|   Please select a valid number  ^|
echo !=================================!

:: Just in case
if  "%choice%"==""  goto  ChooseNumber

goto ChooseNumber


:openEmacs
            echo.
            "C:\Program Files\Emacs\emacs-29.1\bin\runemacs.exe"
	goto end


:openEmacsInit
            echo.
	start "" "C:\Users\diego\.emacs.d\init.el"
	goto end

:openEmacsFolder
            echo.
	start "" "C:\Users\diego\.emacs.d"
	goto end

:end
    set "choice="
