@echo off
del tests\0out.bmp
cls
gcc test.c -o test.exe
test.exe