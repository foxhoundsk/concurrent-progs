#ifndef _RING_BUF_H
#define _RING_BUF_H

#include <stdint.h>

typedef struct rb {
    int head; /* producer */
    int tail; /* consumer */
    int len; /* TODO benchmark whether constant-ize this brings better performance. */
    char *b;
} rb_t;

static __attribute__((const, always_inline))
bool is_power_of_2(const unsigned long n)
{
	return (n != 0 && ((n & (n - 1)) == 0));
}

/*
 * Alloc a ringbuf.
 *
 * @len Size of a single entry.
 * @cnt Counts of entries desired. Final length would be power-of-2.
 *
 * Return address pointing to the allocated ringbuf. NULL on failure,
 * check errno for details.
 */
static rb_t *rb_init(const size_t len, const size_t cnt)
{
    rb_t *rb;

    rb = cmalloc(1, sizeof(rb_t));
    if (!rb) {
        perror("Error allocating ringbuf internals");
        return NULL;
    }
    rb->b = cmalloc(len, cnt);
    if (!rb->b) {
        perror("Error allocating ringbuf buffer");
        free(rb);
        return NULL;
    }

    rb->entry_len = len;

    return rb;
}

/*
 * Return the ringbuf emptiness.
 *
 * @rb Pointer to ringbuf rb_t.
 *
 * Assume the given pointer is valid, reducing redundant branches.
 */
static int rb_is_empty(rb_t *rb)
{
    return rb->h == rb->t;
}

/*
 *
 */
static int rb_read(rb_t *rb, int *buf)
{
}
#endif
