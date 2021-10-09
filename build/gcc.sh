#!/bin/bash
arm-none-eabi-gcc -fPIE -mthumb -march=armv7-m -ffreestanding "$@"
