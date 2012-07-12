#include <string.h>

typedef struct CorcString_ CorcString;

struct CorcString_
{
    char *string;
    char *end;
    size_t len;
    size_t size;
};

extern size_t corcstr_concat_raw(char *dst, const char *src, size_t siz);
extern size_t corcstr_copy_raw(char *dst, const char *src, size_t siz);

extern CorcString *corkstr_create(void);
extern size_t corcstr_append(CorcString *cs, const char *src, size_t len);
extern size_t corcstr_remove(CorcString *cs, size_t len);

extern CorcString *corkstr_join(char **words, char sep, size_t count);

static inline size_t corcstr_resize(CorcString *cs, size_t siz)
{
    cs->string = realloc(cs->string, siz);
    cs->size = siz;
}

static inline size_t corcstr_append_char(CorcString *cs, char c)
{
    if ((cs->len + 1) == cs->size)
        corcstr_resize(cs, cs->size + 1);
    if (c == '\0')
    {
        *(cs->end + 1) = c;
        return cs->len;
    }

    *(++cs->end) = c;
    return ++cs->len;
}

