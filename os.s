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
    .space  256
    .size   threadctx, 256

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
    ldr r0, =threadctx
    add r0, r0, #64
    ldr r1, =blinking_green
    bl initContext

    ldr r0, =threadctx
    add r0, r0, #128
    ldr r1, =blinking_blue
    bl initContext

    ldr r0, =threadctx
    add r0, r0, #192
    ldr r1, =blinking_red
    bl initContext

    start_os_loop:
    wfe
    b start_os_loop

.size  start_os, .-start_os


.global SysTick_Handler
.section  .text.SysTick_Handler
.type  SysTick_Handler, %function
SysTick_Handler:
    push {lr}

    ldr r0, =MsCount
    ldr r1, [r0]
    add r1, r1, #1
    str r1, [r0]

    ldr r0, =threadidx
    ldr r0, [r0]
    lsl r0, r0, #6
    ldr r1, =threadctx
    add r0, r1, r0
    add r1, sp, #4
    bl saveContext

    ldr r1, =threadidx
    ldr r0, [r1]
    add r0, r0, #1
    teq r0, #4  // max threads
    bne systick_none
    mov r0, #1
    systick_none:
    str r0, [r1]
    lsl r0, r0, #6
    ldr r1, =threadctx
    add r0, r1, r0
    add r1, sp, #4
    bl restoreContext

    pop {lr}
    bx lr

.size SysTick_Handler, .-SysTick_Handler

.section  .text.saveContext
.type  saveContext, %function
// param: context_address, stack_address
saveContext:
    add r0, r0, #32
    stmia r0, {r4-r11}
    sub r0, r0, #32
    ldmia r1, {r1-r8}
    stmia r0, {r1-r8}
    bx lr
.size  saveContext, .-saveContext

.section  .text.restoreContext
.type  restoreContext, %function
// param: context_address, stack_address
restoreContext:
    ldmia r0!, {r2-r9}
    stmia r1, {r2-r9}
    ldmia r0, {r4-r11}
    bx lr
.size  restoreContext, .-restoreContext


.section  .text.initContext
.type  initContext, %function
// param: context_address, thread_address
initContext: 
    str r1, [r0, #24]
    mov r1, #1
    lsl r1, r1, #24
    str r1, [r0, #28]
    bx lr
.size  initContext, .-initContext


.global waitevent
.section  .text.waitevent
.type  waitevent, %function
waitevent:
    wfe
    bx lr
.size  waitevent, .-waitevent
