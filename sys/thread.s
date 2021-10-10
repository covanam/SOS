.include "../sys/asm.h"



BEGIN start_thread
    @param entry address
    /* return value from SVC in r4 */
    push {r4}
    svc #1
    mov r0, r4
    pop {r4}
    bx lr
END start_thread
