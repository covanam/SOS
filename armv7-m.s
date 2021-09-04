.include "asm.h"



MEMORY savedStackPointer, 4



BEGIN enableSysTick
    /* systick every 1ms */
    ldr r0, =0xE000E010
    ldr r1, =16000
    str r1, [r0, #4]
    str r1, [r0, #8]
    mov r1, #7
    str r1, [r0]

    bx lr
END enableSysTick



BEGIN SysTick_Handler
    push {r4-r11}

    ldr r0, =savedStackPointer
    str sp, [r0]

    bl OS_Handler

    mov lr, #-7
    bx lr
END SysTick_Handler



BEGIN initThreadStack
    @param: stack pointer
    @param: thread entry address
    @return: initialized stack pointer

    sub r0, r0, #64

    str r1, [r0, #56]

    mov r2, #1
    lsl r2, r2, #24
    str r2, [r0, #60]

    bx lr

END initThreadStack



BEGIN returnToThread
    @param: location to save current stack pointer
    @param: new thread's stack pointer

    ldr r2, =savedStackPointer
    ldr r2, [r2]
    str r2, [r0]

    mov sp, r1
    pop {r4-r11}

    mov lr, #-7
    bx lr

END returnToThread



BEGIN idle
    wfi
    bx lr
END idle
