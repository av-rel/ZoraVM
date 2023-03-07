@echo off

set com=tcc
set fl=zoravm\main.c
set bin=bin\zvm.exe
set args=-std=c99 

if not exist bin mkdir bin
@echo on
echo Building %fl% : %bin%
@echo off
call %com% %args% %fl% -o %bin%
