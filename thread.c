#include "thread.h"
#include "armv7-m.h"

#define STACKSIZE 1024u

extern char _estack;

struct Thread startThread(void* function) {
    /* first slot is reserved for idle thread */
    static int free_slot = 1;

    void *stack = &_estack - free_slot * STACKSIZE;

    stack = initThreadStack(stack, function);

    free_slot++;

    struct Thread ret = {stack};
    return ret;
}