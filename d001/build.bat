@ECHO off
SETLOCAL
CLS
gcc --version
::::::::::::::::::::::::::::::::::::::::::::::::::::
SET "APP_FILE=APP.exe"
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
:BUILD_
    CALL :BLANK_LINE
    
    DEL /s /q /f *.o
    
    ::g++ -c ___msgPublish.hpp -o ___msgPublish.o -std=c++11 -Wall -Wextra
    ::g++ -c _testClass.hpp -o _testClass.o
    ::g++ -c ___msgPublish.hpp -o ___msgPublish.o
    ::g++ -c ___msgSubscribe.h -o ___msgSubscribe.o    
    
    ::g++ ___msgPublish.o ___msgSubscribe.o -o ___msgPS.o    

    ::g++ -c -fPIC ___msgPublish.hpp ___msgSubscribe.h
    ::g++ file1.o file2.o file3.o -shared -o libProject.so -Wl,--whole-archive libAlgatorc.a -Wl,--no-whole-archive
    
    ::g++ -fPIC ___msgPublish.hpp ___msgSubscribe.h -shared -o ___msgPS.o -Wl,--whole-archive -lAlgatorc -Wl,--no-whole-archive
    ::g++ -fPIC ___msgPublish.hpp ___msgSubscribe.h -shared -o ___msgPS.o -Wl,--subsystem,windows--whole-archive -lAlgatorc -Wl,--no-whole-archive
  
 
    ::g++ -O0 -g3 -Wall -c -fmessage-length=0 -o app.o main.cpp  ___msgSubscribe.o ___msgPublish.o _testClass.o
    ::g++ -g -o %APP_FILE% app.o -Wwrite-strings

    g++ ___msgSubscribe.h ___msgPublish.hpp _testClass.hpp main.cpp -o %APP_FILE%

    GOTO :BUILD_END 
:BUILD_010
    CALL :CLEAN_TARGET    
    
    CALL :BLANK_LINE
    CALL %APP_FILE%
    GOTO :BUILD_END
::::::::::::::::::::::::::::::::::::::::::::::::::::
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
:BUILD_CLEAN
    CALL :CLEAN_TARGET
:BUILD_CLEAR 
    CALL :CLEAN_TARGET
:BUILD_END
    CALL :BLANK_LINE