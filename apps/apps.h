#ifndef APPS_H
#define APPS_H

struct app {
        const char *name;
        void *entry;
};

extern const struct app app_list[];

#endif /* APPS_H */
