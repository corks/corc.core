#include <stdlib.h>
#include "str.h"

#ifndef CORCSTR_DEFAULT_NEW
#define CORCSTR_DEFAULT_NEW 64
#endif

size_t corcstr_concat_raw(char *dst, const char *src, size_t siz)
{
    char *d;
    const char *s;
    size_t n, dlen;

    n = siz;
    s = src;

    dlen = strnlen(dst, n);
    d = dst + dlen;
    n = siz - dlen;

    if (n == 0)
        return (dlen + strlen(src));

    while (*s != '\0')
    {
        if (n != 1)
        {
            *d++ = *s;
            n--;
        }
        s++;
    }
    *d = '\0';

    return (dlen + (s - src));
}

size_t corcstr_copy_raw(char *dst, const char *src, size_t siz)
{
    char *d;
    const char *s;
    size_t n;

    d = dst;
    s = src;
    n = siz;

    if (n != 0 && --n != 0)
    {
        do
        {
            if ((*d++ = *s++) == 0)
                break;
        } while (--n != 0);
    }

    if (n == 0)
    {
        if (siz != 0)
            *d = '\0';
        s = (s + strlen(s) + 1);
    }

    return (s - src - 1);
}

CorcString *corcstr_create(void)
{
    CorcString *s;

    s = malloc(sizeof(CorcString));
    s->size = corcSTR_DEFAULT_NEW;
    s->string = malloc(corcSTR_DEFAULT_NEW);
    *s->string = '\0';
    s->end = s->string;
    s->len = 0;

    return s;
}

size_t corcstr_append(CorcString *cs, const char *src, size_t len)
{
    char *p;
    const char *s;
    size_t rlen, total;

    if (len == 0)
        rlen = strlen(src);
    else
        rlen = len;

    total = cs->len + rlen;

    if (total > cs->size)
    {
        cs->string = realloc(cs->string, total + 1);
        cs->size = total;
    }

    p = cs->end;
    s = src;

    do
    {
        *p++ = *s;
    } while (*s++);
    *p = '\0';

    cs->end = p;
    cs->len = cs->len + rlen;

    return cs->len;
}
