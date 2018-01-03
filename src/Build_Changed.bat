@echo off

test&cls

echo [ === BUILD CHANGING ... === ] 

::g++ -o demo.exe -g helloworld.cpp

::::::::::::::::::::::::::::::::::::::::::::::::::::
gcc -c -o add_basic.o add_basic.c
gcc -o add_basic.dll -s -shared add_basic.o -Wl,--subsystem,windows
echo build [add_basic.dll] complete ... 

gcc -c -o addtest_basic.o addtest_basic.c
gcc -o addtest_basic.exe -s addtest_basic.o -L. -ladd_basic
echo build [addtest_basic.exe] complete ... 
::::::::::::::::::::::::::::::::::::::::::::::::::::
gcc -c -o add.o add.c -D ADD_EXPORTS
gcc -o add.dll add.o -s -shared -Wl,--subsystem,windows
echo build [add.dll] complete ...

gcc -c -o addtest.o addtest.c
gcc -o addtest.exe -s addtest.o -L. -ladd
echo build [addtest.exe] complete ...

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

g++ -c -DBUILDING_EXAMPLE_DLL example_dll.cpp
g++ -shared -o example_dll.dll example_dll.o -Wl,--out-implib,libexample_dll.a
g++ -c helloworld.cpp
g++ -o demo.exe helloworld.o -L. -lexample_dll
echo build [demo.exe] complete ... 

::::::::::::::::::::::::::::::::::::::::::::::::::::
gcc -c -o add_var.o add_var.c -D ADD_EXPORTS
gcc -o add_var.dll add_var.o -s -shared -Wl,--subsystem,windows
gcc -c -o add_vartest.o add_vartest.c
gcc -o add_vartest.exe -s add_vartest.o -L. -ladd_var
echo build [add_vartest.exe] complete ...

::::::::::::::::::::::::::::::::::::::::::::::::::::
windres -i resource.rc -o resource.o
gcc -o add.dll add.o resource.o -s -shared -Wl,--subsystem,windows,--out-implib,libadd.a
echo Adding Version Information and Comments to your DLL

::::::::::::::::::::::::::::::::::::::::::::::::::::
echo ----------------------------
call add_vartest.exe
::call addtest.exe
::call addtest_basic.exe
::call demo.exe



