.include "asm.h"



BEGIN enterOs
    /* initialize main SP */
    ldr sp, =_end_os_stack

    /* switch to process stack pointer */
    mrs r0, control
    orr r0, #2
    msr control, r0

    /* initialize idle thread stack pointer */
    ldr sp, =_start_os_stack+64

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
    ldr sp, =_end_os_stack

    mov lr, #-3
    bx lr

END returnToThread



BEGIN SVC_Handler
/* this function must preserve r0-r3, as these registers are passed
as arugments from thread service call into service routine */
    push {r4, r5, lr}

    /* retrive the svc command */
    mrs r4, psp
    ldr r4, [r4, #0x18]
    sub r4, #2
    ldrh r4, [r4]

    /* get svc number */
    and r4, #0xff

    /* get the svc function address to run */
    ldr r5, =service_routine
    ldr r4, [r5, r4]

    /* call svc function */
    blx r4

    pop {r4, r5, lr}

    bx lr

    service_routine:
    .word svc_sleep
END SVC_Handler



BEGIN _sleep
    @param duration
    svc #0
    wfi
    bx lr
END _sleep
