#define MINIFMT_IMPL
#include <stdio.h>
#include <string.h>

#include "minifmt.h"

static const char *fmt_str = "Test {row} str 0x{col.h} {test}";

int main(void) {
    const size_t len = strlen(fmt_str);
    char *str = malloc(len + 1);
    memcpy(str, fmt_str, len + 1);

    const Fmt fmt = fmt_compile(str);
    char *res = fmt_fmt_fmt(fmt, (PlaceholderList) {
        .elems = (Placeholder[]) {
            PLACEHOLDER_LONG("col", 26),
            PLACEHOLDER_LONG("row", 2),
            PLACEHOLDER_DOUBLE("test", 1.32)
        },
        .elems_size = 3
    });
    printf("%s\n", res);
    free(res);
    fmt_destroy(fmt);

    free(str);
    return 0;
}
