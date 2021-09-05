#include "os.h"
#include "armv7-m.h"

static uint32_t msCounter;

struct Thread {
	void* stackPtr;
};

static int numThread = 1; // have at least the idle thread
struct Thread threadList[5];

void terminal(void);

void startOs(void) {
    startThread(terminal);

    enterOs();
}

void OS_Handler(void) {
    static int activeThread = 0;
    msCounter++;
    int oldThread = activeThread;

    /* a stupid round-robin scheduler */
    activeThread++;
    if (activeThread == numThread) activeThread = 0;

    returnToThread(
        &threadList[oldThread].stackPtr,
        threadList[activeThread].stackPtr
    );
}

void yield(void) {
    idle();
}

uint32_t getMsCount(void) {
    return msCounter;
}

#define STACKSIZE 1024u
extern char _procstack[];

void startThread(void (*entryAddr)(void)) {
    static int free_stack_slot = 0;
    static int free_thread_slot = 1; // first slot is for idle thread

    void *stack = _procstack - free_stack_slot * STACKSIZE;

    stack = initThreadStack(stack, entryAddr);

    free_stack_slot++;

    threadList[free_thread_slot].stackPtr = stack;

    free_thread_slot++;

    numThread++;
}