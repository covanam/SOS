#include "thread.h"
#include "armv7-m.h"
#include <stdint.h>
#include <memory.h>
#include "thread_list.h"
#include <stdlib.h>

#define THREAD_STACK_SIZE 1024u

void start_thread(void (*addr)(void))
{
	_start_thread((uint32_t)addr);
}

static inline void *align8(void *ptr)
{
	uintptr_t p = (uintptr_t)ptr;
	p = p & ~(uintptr_t)8;
	return (void *)p;
}

void svc_start_thread(void (*addr)(void))
{
	struct thread thr;
	void *stack = malloc(THREAD_STACK_SIZE);
	thr.stack_start = stack;

	stack = align8(stack + THREAD_STACK_SIZE);

	stack = init_thread_stack(stack, addr);

	thr.stackptr = stack;
	thr.state = IDLE;

	insert_thread(thr);
}
