@echo off


:: ==================================================== ::
:: =                      MSVC                        = ::
:: ==================================================== ::

:: MD -> Multi threaded DLL Runtime library
:: Le dice al compilador que use Dll's y no incluya funciones como malloc, printf...
:: ya que las usara de los DLL del sistema como ucrtbase.dll, o msvcrt.dll

:: EHsc ignora los catch en los errores

:: /Fo mueve el .o generado de cada archivo cpp a la carpeta de intermediates

:: /Od Desactiva las optimizaciones

:: /Zi genera un archivo PDB independiente que contiene toda la información de depuración simbólica para su uso con el depurador

:: No usar 2 espacios entre linea y linea, da error al compilar
:: !!!NO dejar espacio despues de ^!!!

:: /Bt Tiempo de compilacion

:: Warnings -> https://learn.microsoft.com/en-us/cpp/build/reference/compiler-option-warning-level?view=msvc-170

:: Compilation
cl /std:c++17 /Od /Zi /MD /EHsc ^
    /Fo"C:\Midnight\bin\intermediates\\" C:\Midnight\src\*.cpp ^
    /Fo"C:\Midnight\bin\intermediates\\" C:\Midnight\src\Application\*.cpp ^
    /Fo"C:\Midnight\bin\intermediates\\" C:\Midnight\src\File\*.cpp ^
    /Fo"C:\Midnight\bin\intermediates\\" C:\Midnight\src\Rendering\OpenGL\Shader\*.cpp ^
    /Fo"C:\Midnight\bin\intermediates\\" C:\Midnight\src\Rendering\OpenGL\Renderer\*.cpp ^
    /Fo"C:\Midnight\bin\intermediates\\" C:\Midnight\src\Entity\*.cpp ^
    /Fo"C:\Midnight\bin\intermediates\\" C:\Midnight\src\ExternalMeshLoader\*.cpp ^
    /Fo"C:\Midnight\bin\intermediates\\" C:\Midnight\src\GUI\*.cpp ^
    /Fo"C:\Midnight\bin\intermediates\\" C:\Midnight\src\Window\*.cpp ^
    /Fo"C:\Midnight\bin\intermediates\\" C:\Midnight\src\Time\*.cpp ^
    /Fo"C:\Midnight\bin\intermediates\\" C:\Midnight\src\Inputs\*.cpp ^
    /Fo"C:\Midnight\bin\intermediates\\" C:\Midnight\dependencies\glad\src\glad.c ^

    /I "C:\Midnight\dependencies\glfw\include" ^
    /I "C:\Midnight\dependencies\glad\include" ^
    /I "C:\Midnight\dependencies\glm" ^

    /link ^
    "C:\Midnight\dependencies\glfw\lib\glfw3.lib" ^
    user32.lib ^
    gdi32.lib ^
    opengl32.lib ^
    shell32.lib ^
    kernel32.lib ^
    legacy_stdio_definitions.lib ^

    /OUT:"C:\Midnight\bin\x64\Midnight.exe"
