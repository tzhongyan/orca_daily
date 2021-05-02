/**
 * Utility functions
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void str_append(char **dest, const char *src)
{
    size_t src_len, dst_len;
    char* p;

    src_len = strlen(src);

    if (src_len == 0) {
        return;
    }

    if (*dest == NULL) {
        dst_len = 0;
        p = (char*)malloc(sizeof(char) * strlen(src) + 1);
    }
    else {
        dst_len = strlen(*dest);
        /* Reallocate enough memory for length of (src+dest) + 1 for '\0' */
        p = (char*)realloc(*dest, sizeof(char) * (src_len + dst_len + 1));
    }
    assert(p != NULL);

    memcpy(p + dst_len, src, src_len);
    p[dst_len + src_len] = '\0';

    *dest = p;
}

void str_truncate(char *str, size_t len)
{
    if ((str == NULL) || (strlen(str) < len)) {
        return;
    }

    str[len] = '\0';
}
