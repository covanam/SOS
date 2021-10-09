#!/bin/bash
cat sos.bin apps/app.bin > final.bin
st-flash --reset write final.bin 0x08000000
rm final.bin
