#!/bin/bash

arm-linux-gcc -Wall -g -c "watchdog.c" -o "watchdog.o"

arm-linux-gcc -o watchdog  watchdog.o -ldevmem


