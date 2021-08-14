.include "asm.h"

OBJECT MsCount, 4
    .word   0

MEMORY threadctx, 16

OBJECT threadidx, 4
    .word   0


BEGIN start_os

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

END start_os



BEGIN SysTick_Handler

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

END SysTick_Handler



BEGIN saveContext 
    @ current thread index

    push {r4-r11}
    ldr r1, =threadctx
    lsl r0, r0, #2
    add r0, r1, r0

    str sp, [r0]

    bx lr

END saveContext



LOCAL restoreContext
    @ thread index

    ldr r1, =threadctx
    lsl r2, r0, #2
    add r1, r1, r2
    ldr sp, [r1]

    pop {r4-r11}
    bx lr

END restoreContext



LOCAL initContext
    @ threadIndex
    @ SP
    @ addr

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

END initContext



BEGIN waitevent
    /* double wfe due to some bug with the chip */
    wfe
    wfe
    bx lr
END waitevent
