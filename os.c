#include "os.h"
#include "armv7-m.h"
#include "thread_list.h"
#include <stdlib.h>

#define THREAD_STACK_SIZE 1024u

static uint32_t counter_ms;

void terminal(void);

static struct thread *last_active_thread;

void start_os(void)
{
	/* insert empty thread presenting this thread */
	struct thread thr;
	thr.state = ACTIVE;
	insert_thread(thr);
	last_active_thread = head_thread();

	start_thread(terminal);

	enter_os();
}

void OS_Handler(void)
{
	counter_ms++;

	for (struct thread *p = head_thread(); p != NULL; p = next_thread(p)) {
		if (p->state == SLEEP &&
		    (counter_ms - p->sleep_start_time) > p->sleep_duration)
			p->state = IDLE;
	}

	struct thread *new_thread = next_thread(last_active_thread);

	while (1) {
		if (new_thread == NULL)
			new_thread = head_thread();

		if (new_thread->state != SLEEP)
			break;

		new_thread = next_thread(new_thread);
	}

	if (new_thread != last_active_thread) {
		if (last_active_thread->state == ACTIVE)
			last_active_thread->state = IDLE;

		new_thread->state = ACTIVE;

		void **last_sp = &last_active_thread->stackptr;

		last_active_thread = new_thread;

		return_to_thread(last_sp, new_thread->stackptr);
	}
}

void sleep(int duration)
{
	_sleep((uint32_t)duration);
}

void svc_sleep(uint32_t duration)
{
	for (struct thread *p = head_thread(); p != NULL; p = next_thread(p)) {
		if (p->state == ACTIVE) {
			p->state = SLEEP;
			p->sleep_start_time = counter_ms;
			p->sleep_duration = (int)duration;
			break;
		}
	}
}

uint32_t get_ms_counter(void)
{
	return counter_ms;
}

void start_thread(void (*addr)(void))
{
	_start_thread((uint32_t)addr);
}

static void *align8(void *ptr)
{
	uintptr_t p = (uintptr_t)ptr;
	p = p & ~(uintptr_t)8;
	return (void *)p;
}

void svc_start_thread(void (*addr)(void))
{
	struct thread thr;
	void *stack = malloc(THREAD_STACK_SIZE) + THREAD_STACK_SIZE;
	stack = align8(stack);

	stack = init_thread_stack(stack, addr);

	thr.stackptr = stack;
	thr.state = IDLE;

	insert_thread(thr);
}
