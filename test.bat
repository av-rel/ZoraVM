@echo off

set com=tcc
set fl=src\main.c
set bin=bin\main.out
set args=-std=c99 

if not exist bin mkdir bin
echo Compiling %fl%
call %com% %args% %fl% -o %bin%
echo Running %bin% examples\print.zsm
call %bin% examples\print.zsm