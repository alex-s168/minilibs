// Define FILELIB_IMPL in a seperate C file and include this header

/*
Copyright 2024 Alexander Nutz

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef FILELIB_H
#define FILELIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readLine(FILE *file)
#ifndef FILELIB_IMPL
;
#else
{
    size_t buf_size = 0;
    size_t buf_cap = 200;
    char *buf = malloc(buf_cap);
    if (buf == NULL)
        return NULL;
    buf[buf_cap - 1] = '\0';

    while (fgets(buf + buf_size, buf_cap - buf_size, file) != NULL) {
        const size_t len = strlen(buf + buf_size);
        if (len == 0)
            break;
        buf_size += len;
        if (buf[buf_size - 1] == '\n') {
            buf_size --;
            if (buf[buf_size - 1] == '\r')
                buf_size --;
            break;
        }
        if (buf_size == buf_cap - 1) {
            buf_cap += 200;
            char *new = realloc(buf, buf_cap);
            if (new == NULL) {
                free(buf);
                return NULL;
            }
            buf = new;
            buf[buf_cap - 1] = '\0';
        }
    }

    buf[buf_size] = '\0';

    if (feof(file) && buf_size == 0) {
        free(buf);
        buf = NULL;
    }

    return buf;
}
#endif

char *readFile(FILE *file)
#ifndef FILELIB_IMPL
;
#else
{
    char *out = malloc(1);
    size_t out_size = 0;

    char *line;
    while ((line = readLine(file)) != NULL) {
        const size_t len = strlen(line);
        char *newbuf = realloc(out, out_size + len + (out_size > 0 ? 2 : 1));
        if (newbuf == NULL) {
            free(out);
            free(line);
            return NULL;
        }
        out = newbuf;
        if (out_size > 0)
            out[out_size ++] = '\n';
        memcpy(out + out_size, line, len);
        out_size += len;

        free(line);
    }

    out[out_size] = '\0';
    return out;
}
#endif

#endif //FILELIB_H
