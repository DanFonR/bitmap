@echo off

clang .\src\bitmap.* .\src\colliding_planets\colliding_planets.c -c -O3 -Wno-deprecated-declarations -Wno-pragma-pack -Wno-unused-command-line-argument
clang .\*.o -o bitmap-gen.exe -O3 -Wno-deprecated-declarations -Wno-pragma-pack -Wno-unused-command-line-argument
del .\src\*.pch
del .\*.o
