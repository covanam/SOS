#ifndef THREAD_H
#define THREAD_H

void *start_thread(void (*entryAddress)(void));

void wait_thread(void *handle);

void detach_thread(void *handle);

#endif
