.syntax unified
.cpu cortex-m4
.fpu softvfp
.thumb


.global MsCount
    .data
    .align  2
    .type   MsCount, %object
    .size   MsCount, 4
MsCount:
    .word   0

    .bss
    .align  2
threadctx:
    .space  16
    .size   threadctx, 16

    .data
    .align  2
    .type   threadidx, %object
    .size   threadidx, 4
threadidx:
    .word   0


.global start_os
.section  .text.start_os
.type  start_os, %function
start_os:
    /* systick every 1ms */
    ldr r0, =0xE000E010
    ldr r1, =16000
    str r1, [r0, #4]
    str r1, [r0, #8]
    mov r1, #7
    str r1, [r0]

    /* initialize thread context */
    mov r0, #1
    ldr r1, =0x2001FFFC
    ldr r2, =blinking_green
    bl initContext

    mov r0, #2
    ldr r1, =0x2001FEFC
    ldr r2, =blinking_blue
    bl initContext

    mov r0, #3
    ldr r1, =0x2001FDFC
    ldr r2, =blinking_red
    bl initContext

    start_os_loop:
    wfe
    b start_os_loop

.size  start_os, .-start_os


.global SysTick_Handler
.section  .text.SysTick_Handler
.type  SysTick_Handler, %function
SysTick_Handler:
    ldr r0, =MsCount
    ldr r1, [r0]
    add r1, r1, #1
    str r1, [r0]

    ldr r0, =threadidx
    ldr r0, [r0]
    bl saveContext

    ldr r1, =threadidx
    ldr r0, [r1]
    add r0, r0, #1
    teq r0, #4  // max threads
    bne systick_none
    mov r0, #1
    systick_none:
    str r0, [r1]
    bl restoreContext

    ldr lr,=0xFFFFFFF9
    bx lr

.size SysTick_Handler, .-SysTick_Handler

.section  .text.saveContext
.type  saveContext, %function
// param: current thread index
saveContext:
    push {r4-r11}
    ldr r1, =threadctx
    lsl r0, r0, #2
    add r0, r1, r0

    str sp, [r0]

    bx lr
.size  saveContext, .-saveContext

.section  .text.restoreContext
.type  restoreContext, %function
// param: thread index
restoreContext:
    ldr r1, =threadctx
    lsl r2, r0, #2
    add r1, r1, r2
    ldr sp, [r1]

    pop {r4-r11}
    bx lr
.size  restoreContext, .-restoreContext


.section  .text.initContext
.type  initContext, %function
// param: thread index, SP, addr
initContext:
    ldr r3, =threadctx
    lsl r0, r0, #2
    add r0, r3, r0

    sub r1, r1, #64
    str r1, [r0]

    str r2, [r1, #56]

    mov r2, #1
    lsl r2, r2, #24
    str r2, [r1, #60]

    bx lr
.size  initContext, .-initContext


.global waitevent
.section  .text.waitevent
.type  waitevent, %function
waitevent:
    /* double wfe due to some bug with the chip */
    wfe
    wfe
    bx lr
.size  waitevent, .-waitevent
