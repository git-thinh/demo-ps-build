@echo off

test&cls

echo [ === CLEAN LIB === ] 


del /s /q /f *.o
del /s /q /f *.a
del /s /q /f *.dll
del /s /q /f *.exe

echo clean all [*.o; *.a, *.dll] complete ...

  