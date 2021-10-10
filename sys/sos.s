.include "../sys/asm.h"



BEGIN sleep
    @param duration
    svc #0
    wfi
    bx lr
END sleep
