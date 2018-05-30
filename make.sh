#!/bin/bash
if [[ $1 = "clean" ]]
then
    rm main.gba
    rm main.elf
    rm main.o
    rm buttons.o
    rm display.o
else
    arm-none-eabi-gcc -c buttons.c -mthumb-interwork -mthumb -O2 -o buttons.o
    arm-none-eabi-gcc -c display.c -mthumb-interwork -mthumb -O2 -o display.o
    arm-none-eabi-gcc -c main.c -mthumb-interwork -mthumb -O2 -o main.o
    arm-none-eabi-gcc buttons.o display.o main.o -mthumb-interwork -mthumb -specs=gba.specs -o main.elf
    #arm-none-eabi-gcc -c test.c -mthumb-interwork -mthumb -O2 -o test.o
    #arm-none-eabi-gcc test.o -mthumb-interwork -mthumb -specs=gba.specs -o main.elf
    arm-none-eabi-objcopy -v -O binary main.elf main.gba
    gbafix main.gba
fi
