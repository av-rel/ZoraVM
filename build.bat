@echo off

set com=gcc
set fl=source\main.c
set bin=bin\zvm.exe
set args=-O3

if not exist bin mkdir bin
@echo on
echo Building %fl% : %bin%
@echo off
call %com% %args% %fl% -o %bin%
