#include <string.h>

typedef struct CorkString CorkString;

struct CorkString
{
    char *string;
    char *end;
    size_t len;
    size_t size;
};

size_t corkstr_concat_raw(char *dst, const char *src, size_t siz);
size_t corkstr_copy_raw(char *dst, const char *src, size_t siz);

CorkString *corkstr_create(void);
size_t corkstr_append(CorkString *cs, const char *src, size_t len);
