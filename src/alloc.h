#ifndef CORC_CORE_ALLOC_H
#define CORC_CORE_ALLOC_H

typedef void (*corc_bad_cb)(void);

void corc_alloc_bad_cb(corc_bad_cb cb);
void *corc_alloc(size_t siz);
void corc_free(void *ptr);

#endif /* CORC_CORE_ALLOC_H */
