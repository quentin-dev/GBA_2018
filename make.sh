#!/bin/bash
if [[ $1 = "clean" ]]
then
    rm main.gba
    rm main.elf
    rm main.o
else
    arm-none-eabi-gcc -c main.c -mthumb-interwork -mthumb -O2 -o main.o
    arm-none-eabi-gcc -c buttons.c -mthumb-interwork -mthumb -O2 -o buttons.o
    arm-none-eabi-gcc main.o buttons.o -mthumb-interwork -mthumb -specs=gba.specs -o main.elf
    arm-none-eabi-objcopy -v -O binary main.elf main.gba
    gbafix main.gba
fi
