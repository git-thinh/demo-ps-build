@ECHO off
SETLOCAL
CLS
gcc --version
::::::::::::::::::::::::::::::::::::::::::::::::::::
SET "APP_FILE=APP.EXE"
SET "PATH_ROOT=%~p1"
SET "CODE=%~n1"
SET "BUILD_CODE=BUILD_%CODE%"

ECHO PATH_ROOT = %PATH_ROOT%
ECHO CODE = %CODE%
ECHO BUILD_CODE = %BUILD_CODE%

CALL :BLANK_LINE
::IF "%CODE%"=="001" GOTO BUILD_001
GOTO %BUILD_CODE%
::::::::::::::::::::::::::::::::::::::::::::::::::::
:BUILD_001    
    CALL :CLEAN_TARGET
    :: Compile the source files into object files
    gcc -c main.cpp -o main.o
    :: Link the object files into a binary
    gcc -o %APP_FILE% main.o -lstdc++    
    CALL :BLANK_LINE
    CALL %APP_FILE%
    GOTO :BUILD_END
:BUILD_002
    CALL :CLEAN_TARGET    
    g++ -o %APP_FILE% main.cpp
    CALL :BLANK_LINE
    CALL %APP_FILE%
    GOTO :BUILD_END
:BUILD_003
    CALL :CLEAN_TARGET    
    g++ -Wall -g -o %APP_FILE% main.cpp
    :: -o: specifies the output executable filename.
    :: -Wall: prints "all" warning messages.
    :: -g: generates additional symbolic debuggging information for use with gdb debugger.
    CALL :BLANK_LINE
    CALL %APP_FILE%
    GOTO :BUILD_END
:BUILD_004
    CALL :CLEAN_TARGET    
    :: Compile and Link Separately
    :: The above command compile the source file into object file 
    :: and link with other object files (system library) into executable in one step. 
    :: You may separate compile and link in two steps as follows:
    :: Compile-only with -c option
    :: Compile the source files into object files
    g++ -c -Wall -g main.cpp
    :: Link object file(s) into an executable
    g++ -g -o %APP_FILE% main.o
    :: The options are:
    :: -c: compile into object file "Hello.o". By default, the object file has the same name as 
    :: the source file with extension of ".o" (there is no need to specify -o option). 
    :: No linking with other object file or library.
    :: Linking is performed when the input file are object files ".o" 
    :: (instead of source file ".cpp" or ".c"). 
    :: GCC uses a separate linker program (called ld.exe) to perform the linking.
    CALL :BLANK_LINE
    CALL %APP_FILE%
    GOTO :BUILD_END
:BUILD_005
    CALL :CLEAN_TARGET    
    :: Compile and Link Multiple Source Files
    :: Suppose that your program has two source files: file1.cpp, file2.cpp. 
    :: You could compile all of them in a single command:
    g++ -o %APP_FILE% file1.cpp file2.cpp 
    :: However, we usually compile each of the source files separately into object file, 
    :: and link them together in the later stage. 
    :: In this case, changes in one file does not require re-compilation of the other files.
    g++ -c file1.cpp
    g++ -c file2.cpp
    g++ -o %APP_FILE% file1.o file2.o    

    CALL :BLANK_LINE
    CALL %APP_FILE%
    GOTO :BUILD_END
::::::::::::::::::::::::::::::::::::::::::::::::::::
:CLEAN_TARGET
    DEL /s /q /f *.o
    DEL /s /q /f *.a
    DEL /s /q /f *.dll
    DEL /s /q /f *.exe    
    CALL :BLANK_LINE
EXIT /B 0

:BLANK_LINE 
    ECHO.
    ECHO.
    ECHO.
EXIT /B 0

:BUILD_END
    CALL :BLANK_LINE