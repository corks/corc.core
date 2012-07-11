#include <string.h>

typedef struct CorcString CorcString;

struct CorcString
{
    char *string;
    char *end;
    size_t len;
    size_t size;
};

size_t corcstr_concat_raw(char *dst, const char *src, size_t siz);
size_t corcstr_copy_raw(char *dst, const char *src, size_t siz);

CorcString *corkstr_create(void);
size_t corcstr_append(CorcString *cs, const char *src, size_t len);
