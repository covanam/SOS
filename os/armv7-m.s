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
    sub sp, #8
    mov r0, sp
    bl OS_Handler
    pop {r0, r1}

    /* save current context, unless sp_save_addr==NULL */
    cmp r0, #0
    ittt ne
    mrsne r2, psp
    stmdbne r2!, {r4-r11}
    strne r2, [r0]

    /* restore new context, unless new_sp==NULL */
    cmp r1, #0
    itt ne
    ldmiane r1!, {r4-r11}
    msrne psp, r1

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

    /* initialize LR with thread end code */
    ldr r3, =.Lthread_end_code
    orr r3, #1
    str r3, [r0, #52]

    bx lr

    .Lthread_end_code:
    svc #2
    .Letl: wfi
    b .Letl

END init_thread_stack



BEGIN SVC_Handler
    /* note: r0-r3 must be preserved as they are passed to the svc functions */

    push {r4-r6, lr}

    /* get interrupt stack (check LR to see if it's MSP or PSP) */
    cmp lr, #-3
    ite eq
    mrseq r4, psp
    addne r4, sp, #16

    /* retrive the svc instruction's encoding */
    ldr r5, [r4, #0x18]
    sub r5, #2
    ldrh r5, [r5]

    /* get svc number */
    and r5, #0xff

    /* get the svc function address to run */
    ldr r6, =.Lservice_routine
    lsl r5, #2
    ldr r5, [r6, r5]

    /* call svc function */
    blx r5

    /* return value */
    str r0, [r4]

    pop {r4-r6, lr}

    bx lr

    .Lservice_routine:
    .word sleep
    .word start_thread
    .word end_thread
END SVC_Handler
