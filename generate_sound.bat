@echo off

cd sound

rasm compile_at2_files.asm -o UniversalAt2Files -s -sl -sq

Disark UniversalAt2Files.bin At2Files.asm --symbolFile UniversalAt2Files.sym --sourceProfile sdcc

copy At2Files.asm ..\src\audio\At2Files.asm

cd ..
