#ifndef MUTEX_H
#define MUTEX_H

#include <stdint.h>

struct mutex {
        uint8_t is_locked;
};

void mutex_init(struct mutex *m);

void mutex_lock(struct mutex *m);

void mutex_release(struct mutex *m);

#endif /* MUTEX_H */
