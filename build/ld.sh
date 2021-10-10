#!/bin/bash
linker_script="$(dirname -- "$0")/linker.ld"
arm-none-eabi-ld -T$linker_script --orphan-handling=error -nostdlib "$@"
