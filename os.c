#include "os.h"
#include "armv7-m.h"

static uint32_t counter_ms;

enum thread_state { ACTIVE, IDLE, SLEEP };

struct thread {
	void *stackptr;
	enum thread_state state;
	uint32_t sleep_start_time;
	int sleep_duration;
};

static int num_thread = 1; // have at least the idle thread
struct thread thread_list[50];

void terminal(void);

void start_os(void)
{
	/* first thread, idle thread, is the first one to be active */
	thread_list[0].state = ACTIVE;

	start_thread(terminal);

	enter_os();
}

void OS_Handler(void)
{
	static int active_thread = 0;
	counter_ms++;
	int last_thread = active_thread;

	/* wake up sleeping threads if time up */
	for (int i = 0; i < num_thread; ++i) {
		struct thread *pt = &thread_list[i];
		if (pt->state == SLEEP &&
		    (counter_ms - pt->sleep_start_time) > pt->sleep_duration)
			thread_list[i].state = IDLE;
	}

	/* find a new thread to run */
	while (1) {
		active_thread++;
		if (active_thread == num_thread)
			active_thread = 0;

		struct thread *pt = &thread_list[active_thread];

		if (pt->state == SLEEP) {
			continue;
		} else if (pt->state == IDLE) {
			break;
		} else if (active_thread == last_thread) {
			if (pt->state == SLEEP) {
				active_thread = 0;
			}
			break;
		} else {
			/* never reach this */
		}
	}

	if (active_thread != last_thread) {
		if (thread_list[last_thread].state == ACTIVE)
			thread_list[last_thread].state = IDLE;

		thread_list[active_thread].state = ACTIVE;

		return_to_thread(&thread_list[last_thread].stackptr,
				 thread_list[active_thread].stackptr);
	}
}

void sleep(int duration)
{
	_sleep((uint32_t)duration);
}

void svc_sleep(uint32_t duration)
{
	for (int i = 0; i < num_thread; ++i) {
		if (thread_list[i].state == ACTIVE) {
			thread_list[i].state = SLEEP;
			thread_list[i].sleep_start_time = counter_ms;
			thread_list[i].sleep_duration = (int)duration;
			break;
		}
	}
}

uint32_t get_ms_counter(void)
{
	return counter_ms;
}

#define STACKSIZE 1024u
extern char _procstack[];

void start_thread(void (*addr)(void))
{
	_start_thread((uint32_t)addr);
}

void svc_start_thread(void (*addr)(void))
{
	static int free_stack_slot = 0;
	static int free_thread_slot = 1; // first slot is for idle thread

	void *stack = _procstack - free_stack_slot * STACKSIZE;

	stack = init_thread_stack(stack, addr);

	free_stack_slot++;

	thread_list[free_thread_slot].stackptr = stack;
	thread_list[free_thread_slot].state = IDLE;

	free_thread_slot++;

	num_thread++;
}
