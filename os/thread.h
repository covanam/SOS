#ifndef THREAD_H
#define THREAD_H

#include <stdint.h>

enum thread_state { ACTIVE, IDLE, SLEEP };

struct thread {
	void *stack_start;
	void *stackptr;
	enum thread_state state;
	uint32_t sleep_start_time;
	unsigned int sleep_duration;
	char *handle;
};

void start_thread(void (*addr)(void), void *handle);

#endif
