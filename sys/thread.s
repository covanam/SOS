.include "../sys/asm.h"



BEGIN start_thread
    @param entry address
    @ret handle pointer
    push {r0, lr}
    mov r0, #1
    bl malloc
    mov r1, r0
    pop {r0, lr}
    svc #1
    /* svc call preserves r0-r3 */
    mov r0, r1
    bx lr
END start_thread



BEGIN wait_thread
    @param handle pointer
    .Lwait_thread_loop:
    ldrb r1, [r0]
    cmp r1, #0
    itt eq
    wfieq
    beq .Lwait_thread_loop

    push {r0, lr}
    bl free
    pop {r0, lr}

    bx lr
END wait_thread



BEGIN detach_thread
    @param handle pointer
    push {r0, lr}
    bl free
    pop {r0, lr}

    bx lr
END detach_thread
