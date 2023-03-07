@echo off

set com=tcc
set src=src\main.c
set test=examples\print.zsm

if not exist bin mkdir bin
call %com% %src% -o bin\main.exe -std=c99 -O3 
call bin\main.exe %test%