@ECHO off
setlocal
test&cls
gcc --version
::::::::::::::::::::::::::::::::::::::::::::::::::::
SET "PATH_ROOT=%~p1"
SET "CODE=%~n1"
SET "BUILD_CODE=BUILD_%CODE%"

ECHO PATH_ROOT = %PATH_ROOT%
ECHO CODE = %CODE%
ECHO BUILD_CODE = %BUILD_CODE%

::IF "%CODE%"=="001" GOTO BUILD_001
GOTO %BUILD_CODE%
::::::::::::::::::::::::::::::::::::::::::::::::::::

:BUILD_001
    ECHO.  
    :: Clean target  
    DEL /s /q /f *.o
    DEL /s /q /f *.a
    DEL /s /q /f *.dll
    DEL /s /q /f *.exe

    :: Compile the source files into object files
    gcc -c main.cpp -o main.o

    :: Link the object files into a binary
    gcc -o app.exe main.o -lstdc++

    call app.exe
    GOTO :BUILD_END
::::::::::::::::::::::::::::::::::::::::::::::::::::
:BUILD_END
    ECHO.
    ECHO.
    ECHO.