.syntax unified
.cpu cortex-m4
.fpu softvfp
.thumb

.macro BEGIN name:req
    .global \name
    .section  .text
    .type  \name, %function
    \name\():
.endm

.macro END name:req
    .size  \name, .-\name
.endm

.macro LOCAL name
    .section  .text
    .type \name, %function
    \name\():
.endm

.macro OBJECT name:req, size:req
    .global \name
    .data
    .align  2
    .type   \name, %object
    .size   \name, \size
    \name\():
.endm

.macro MEMORY name:req, size:req
    .bss
    .align  2
    .size   \name, \size
    \name\():
    .space  16
.endm
