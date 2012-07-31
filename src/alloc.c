#ifdef CORC_VERBOSE
#   include <stdio.h>
#endif
#include <stdlib.h>
#include "alloc.h"

static void bad_callback(void)
{
#ifdef CORC_VERBOSE
    fprintf(stderr, "Memory allocation failed. Exiting to avoid more things breaking...\n");
#endif
    exit(1);
}

static corc_bad_cb alloc_cb = bad_callback;
 
void corc_alloc_bad_cb(corc_bad_cb cb)
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

void corc_free(void *ptr)
{
    free(ptr);
}
