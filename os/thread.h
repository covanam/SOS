#ifndef THREAD_H
#define THREAD_H

#include <stdint.h>

enum thread_state { ACTIVE, IDLE, SLEEP };

struct thread_handle {
        uint8_t done;
};

struct thread {
	void *stack_start;
	void *stackptr;
	enum thread_state state;
	uint32_t sleep_start_time;
	int sleep_duration;
};

void start_thread(void (*entryAddress)(void));

#endif
