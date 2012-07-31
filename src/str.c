#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "alloc.h"
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

    s = corc_alloc(sizeof(CorcString));
    if (s == NULL)
    {
        printf("corc_alloc broke: %d", __LINE__);
        exit(1);
    }
    s->size = CORCSTR_DEFAULT_NEW;
    s->string = corc_alloc(CORCSTR_DEFAULT_NEW);
    if (s->string == NULL)
    {
        printf("corc_alloc broke: %d", __LINE__);
        exit(1);
    }
    *s->string = '\0';
    s->end = s->string;
    s->len = 0;

    return s;
}

void corcstr_destroy(CorcString *cs)
{
    if (cs == NULL)
        return;

    if (cs->string != NULL)
        free(cs->string);
    free(cs);
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
        corcstr_resize(cs, total + 1);

    p = cs->end;
    s = src;

    while (*s)
    {
        *p++ = *s++;
    }
    *p = '\0';

    cs->end = p;
    cs->len = cs->len + rlen;

    return cs->len;
}

size_t corcstr_remove(CorcString *cs, size_t len)
{
    int i;
    char *start;

    i = 0;
    start = cs->end - (len + 1);

    while (--len && *start != '\0')
    {
        *start++ = '\0';
        i++;
    }
    cs->len = cs->len - i;

    return cs->len;
}

CorcString *corcstr_join(char **words, char sep, size_t count)
{
    unsigned int i;
    CorcString *cs;
    cs = corcstr_create();

    for (i = 0; i < count; ++i)
    {
        corcstr_append(cs, words[i], sizeof(words[i]));
        corcstr_append_char(cs, sep);
    }

    return cs;
}

CorcString **corcstr_split(CorcString *in, char sep)
{
    int i = 0;
    char *instr, *ptr, *placeholder;
    CorcString **out;

    instr = strdup(in->string);
    out = corc_alloc(sizeof(CorcString));
    placeholder = instr;

    while ((ptr = strchr(placeholder, sep)))
    {
        *ptr = '\0';
        out[i] = corcstr(placeholder);
        placeholder = ptr+1;
        ++i;
    }
    if (placeholder)
    {
        out[i] = corcstr(placeholder);
        out[++i] = NULL;
    }
    else if (i == 0)
    {
        free(instr);
        return NULL;
    }

    free(instr);
    return out;
}
