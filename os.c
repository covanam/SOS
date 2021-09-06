#include "os.h"
#include "armv7-m.h"

static uint32_t msCounter;

enum ThreadState {
    ACTIVE, IDLE, SLEEP
};

struct Thread {
	void* stackPtr;
    enum ThreadState state;
    uint32_t sleepStartTime;
    int sleepDuration;
};

static int numThread = 1; // have at least the idle thread
struct Thread threadList[50];

void terminal(void);

void startOs(void) {
    /* first thread, idle thread, is the first one to be active */
    threadList[0].state = ACTIVE;

    startThread(terminal);

    enterOs();
}

void OS_Handler(void) {
    static int activeThread = 0;
    msCounter++;
    int oldThread = activeThread;

    /* wake up sleeping threads if time up */
    for (int i = 0; i < numThread; ++i) {
        struct Thread *pt = &threadList[i];
        if (pt->state == SLEEP && (msCounter - pt->sleepStartTime) > pt->sleepDuration )
            threadList[i].state = IDLE;
    }

    /* find a new thread to run */
    while (1) {
        activeThread++;
        if (activeThread == numThread)
            activeThread = 0;

        struct Thread *pt = &threadList[activeThread];

        if (pt->state == SLEEP) {
            /* do not active sleeping thread */
            continue;
        }
        else if (pt->state == IDLE) {
            /* new thread has been found */
            break;
        }
        else if (activeThread == oldThread) {
            /* couldn't find any new thread to run */
            if (pt->state == SLEEP) {
                /* current thread has been put to sleep, run idle thread */
                activeThread = 0;
            }
            else {
                /* keep running the current thread */
            }

            break;
        }
        else {
            /* never reach this */
        }
    }

    if (activeThread != oldThread) {
        if (threadList[oldThread].state == ACTIVE)
            threadList[oldThread].state = IDLE;

        threadList[activeThread].state = ACTIVE;

        returnToThread(
            &threadList[oldThread].stackPtr,
            threadList[activeThread].stackPtr
        );
    }
}

void sleep(int duration) {
    _sleep((uint32_t)duration);
}

void SVC_Handler(uint32_t duration) {
    for (int i = 0; i < numThread; ++i) {
        if (threadList[i].state == ACTIVE) {
            threadList[i].state = SLEEP;
            threadList[i].sleepStartTime = msCounter;
            threadList[i].sleepDuration = (int)duration;
            break;
        }
    }
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
    threadList[free_thread_slot].state = IDLE;

    free_thread_slot++;

    numThread++;
}