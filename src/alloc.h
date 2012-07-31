#ifndef CORC_CORE_ALLOC_H
#define CORC_CORE_ALLOC_H

extern void corc_alloc_bad_cb(void (*cb)(void));
void *corc_alloc(size_t siz);

#endif /* CORC_CORE_ALLOC_H */
