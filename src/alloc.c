#include <stdio.h>
#include <stdlib.h>
#include "alloc.h"

static void (*alloc_cb)(void);

void corc_alloc_bad_cb(void (*cb)(void))
{
    alloc_cb = cb;
}

void *corc_alloc(size_t siz)
{
    void *p;
    p = malloc(siz);

    if (p == NULL)
        alloc_cb();

    return p;
}
