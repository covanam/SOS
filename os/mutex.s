.include "asm.h"



BEGIN mutex_init
        @param mutex pointer
        movs.n r1, #0
        strb r1, [r0]
        bx lr
END mutex_init



BEGIN mutex_lock
        @param mutex pointer
        movs r2, #1
        b .Lfirst_try

        .Lretry:
        wfi

        .Lfirst_try:
        ldrexb r1, [r0]
        cmp r1, #0
        bne .Lretry

        strexb r1, r2, [r0]
        cmp r1, #0
        bne .Lretry

        dmb
        bx lr
END mutex_lock



BEGIN mutex_release
        @param mutex pointer
        dmb
        mov r1, #0
        strb r1, [r0]
        bx lr
END mutex_release
