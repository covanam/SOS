#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "thread_list.h"

struct node {
	struct thread thread;
	struct node *next;
};

static struct node *head = NULL;

int insert_thread(struct thread t)
{
	struct node *nnode = malloc(sizeof(struct node));

	if (nnode != NULL) {
		nnode->next = head;
		head = nnode;
		nnode->thread = t;
	}

	return nnode != NULL;
}

struct thread *head_thread(void)
{
	return &head->thread;
}

struct thread *next_thread(const struct thread *current)
{
	struct thread *ret = NULL;
	if (current != NULL) {
		size_t off = offsetof(struct node, thread);
		struct node *n = (void *)(current - off);
		ret = &n->next->thread;
	}
	return ret;
}
