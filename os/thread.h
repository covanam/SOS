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
	unsigned int sleep_duration;
	struct thread_handle *handle;
};

struct thread_handle *start_thread(void (*entryAddress)(void));
void wait_thread(struct thread_handle*);
void detach_thread(struct thread_handle*);

#endif
