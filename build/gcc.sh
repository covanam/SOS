#!/bin/bash
arm-none-eabi-gcc -fPIC -mthumb -march=armv7-m -ffreestanding "$@"
