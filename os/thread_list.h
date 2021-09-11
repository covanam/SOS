#ifndef THREAD_LIST_H
#define THREAD_LIST_H

#include "thread.h"

int insert_thread(struct thread t);
struct thread *head_thread(void);
struct thread *next_thread(const struct thread *current);
int remove_thread(struct thread *t);

#endif /* THREAD_LIST_H */
