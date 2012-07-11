#include <string.h>

typedef struct YnysString YnysString;

struct YnysString
{
    char *string;
    char *end;
    size_t len;
    size_t size;
};

size_t ynys_str_concat_raw(char *dst, const char *src, size_t siz);
size_t ynys_str_copy_raw(char *dst, const char *src, size_t siz);

YnysString *corkstr_create(void);
size_t ynys_str_append(YnysString *cs, const char *src, size_t len);
