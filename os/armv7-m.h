#ifndef ARMV7_M_H
#define ARMV7_M_H

#include <stdint.h>
#include "thread.h"

__attribute__((noreturn)) void enter_os(void);
void *init_thread_stack(void *sp, void *addr);
void return_to_thread(void **p_old_sp, void *new_sp);
void _sleep(uint32_t duration);
struct thread_handle *_start_thread(uint32_t addr);

#endif
