.include "asm.h"



BEGIN enter_os
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

    .LOsIdleLoop:
    wfi
    b .LOsIdleLoop
END enter_os



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



BEGIN init_thread_stack
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

END init_thread_stack



BEGIN return_to_thread
    @param: location to save current stack pointer
    @param: new thread's stack pointer

    /* save current stack pointer */
    mrs r2, psp
    str r2, [r0]

    /* restore r4-r11 (the rest is restored upon exception return) */
    ldmia r1!, {r4-r11}

    /* load new stack pointer */
    msr psp, r1

    /* reset main stack pointer to initial value */
    ldr sp, =_end_os_stack

    mov lr, #-3
    bx lr

END return_to_thread



BEGIN SVC_Handler
    /* get interrupt stack (check LR to see if it's MSP or PSP) */
    cmp lr, #-3
    ite eq
    mrseq r0, psp
    movne.n r0, sp

    /* retrive the svc instruction's encoding */
    ldr r1, [r0, #0x18]
    sub r1, #2
    ldrh r1, [r1]

    /* get svc number */
    and r1, #0xff

    /* get the svc function address to run */
    ldr r2, =.Lservice_routine
    lsl r1, #2
    ldr r1, [r2, r1]

    /* pass original argument to svc function */
    ldr r0, [r0]

    /* call svc function */
    push {lr}
    blx r1
    pop {lr}

    bx lr

    .Lservice_routine:
    .word svc_sleep
    .word svc_start_thread
END SVC_Handler



BEGIN _sleep
    @param duration
    svc #0
    wfi
    bx lr
END _sleep



BEGIN _start_thread
    @param entry address
    svc #1
    bx lr
END _start_thread
