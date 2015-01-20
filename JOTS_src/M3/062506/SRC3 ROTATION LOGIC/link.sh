#!/bin/bash

arm-linux-gcc -Wall -g -c "commands.c" -o "commands.o"
arm-linux-gcc -Wall -g -c "LogEvents.c" -o "LogEvents.o"
arm-linux-gcc -Wall -g -c "csv.c" -o "csv.o"
arm-linux-gcc -Wall -g -c "input.c" -o "input.o"
arm-linux-gcc -Wall -g -c "serial.c" -o "serial.o"
arm-linux-gcc -Wall -g -c "settings.c" -o "settings.o"
arm-linux-gcc -Wall -g -c "main.c" -o "main.o"
arm-linux-gcc -Wall -g -c "gpio.c" -o "gpio.o"
arm-linux-gcc -Wall -g -c "iniparse/iniparser.c" -o "iniparse/iniparser.o"
arm-linux-gcc -Wall -g -c "iniparse/dictionary.c" -o "iniparse/dictionary.o"
arm-linux-gcc -Wall -g -c "iniparse/strlib.c" -o "iniparse/strlib.o"
arm-linux-gcc -Wall -g -c "PrintAndApply.c" -o "PrintAndApply.o"

arm-linux-gcc -o aik2 main.o input.o commands.o gpio.o serial.o csv.o settings.o iniparse/iniparser.o iniparse/dictionary.o iniparse/strlib.o PrintAndApply.o LogEvents.o -ldevmem

