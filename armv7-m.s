.include "asm.h"



BEGIN enterOs
    /* initialize main SP, reserve 64 bytes for idle thread */
    ldr sp, =_estack-64

    /* switch to process stack pointer */
    mrs r0, control
    orr r0, #2
    msr control, r0

    /* initialize process stack pointer */
    ldr sp, =_estack

    /* systick every 1ms */
    ldr r0, =0xE000E010
    ldr r1, =16000
    str r1, [r0, #4]
    str r1, [r0, #8]
    mov r1, #7
    str r1, [r0]

    OsIdleLoop:
    wfi
    b OsIdleLoop
END enterOs



BEGIN SysTick_Handler
    mrs r0, psp
    stmdb r0!, {r4-r11}
    msr psp, r0

    bl OS_Handler

    mrs r0, psp
    add r0, #32
    msr psp, r0

    mov lr, #-3
    bx lr
END SysTick_Handler



BEGIN initThreadStack
    @param: stack pointer
    @param: thread entry address
    @return: initialized stack pointer

    sub r0, r0, #64 // a saved thread needs 64 bytes

    /* initialize return address */
    str r1, [r0, #56]

    /* initialize xPSR with only Thumb bit = 1 */
    mov r2, #1
    lsl r2, r2, #24
    str r2, [r0, #60]

    bx lr

END initThreadStack



BEGIN returnToThread
    @param: location to save current stack pointer
    @param: new thread's stack pointer

    /* save current stack pointer */
    mrs r2, psp
    str r2, [r0]

    /* restore new thread's r4-r11 (the rest is restored upon exception return) */
    ldmia r1!, {r4-r11}

    /* load new stack pointer */
    msr psp, r1

    /* reset main stack pointer to initial value */
    ldr sp, =_estack-64

    mov lr, #-3
    bx lr

END returnToThread



BEGIN idle
    wfi
    bx lr
END idle
