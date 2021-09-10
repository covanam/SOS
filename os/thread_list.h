#ifndef THREAD_LIST_H
#define THREAD_LIST_H

enum thread_state { ACTIVE, IDLE, SLEEP };

struct thread {
	void *stack_start;
	void *stackptr;
	enum thread_state state;
	uint32_t sleep_start_time;
	int sleep_duration;
};

int insert_thread(struct thread t);
struct thread *head_thread(void);
struct thread *next_thread(const struct thread *current);
int remove_thread(struct thread *t);

#endif /* THREAD_LIST_H */
