#define FILELIB_IMPL
#include "filelib.h"
#define MINICONF_IMPL
#include "miniconf.h"
#define MINIFMT_IMPL
#include "minifmt.h"

#include <stdio.h>
#include <string.h>

static int miniconf() {
    Config cfg;
    config_init(&cfg);

    FILE *file = fopen("test.miniconf", "r");
    const AllocGroup file_alloc = config_add_file(&cfg, file);
    fclose(file);

    bool ok;
    const char *value = config_get_str_at(cfg, "status bar/normal/format", &ok);
    printf("%i: %s\n", ok, value);

    allocgroup_free(file_alloc);
    config_destroy(&cfg);

    return 0;
}

static const char *fmt_str = "Test {row} str 0x{col.h} {test}";

static int minifmt(void) {
    const size_t len = strlen(fmt_str);
    char *str = malloc(len + 1);
    memcpy(str, fmt_str, len + 1);

    const Fmt fmt = fmt_compile(str);
    char *res = fmt_fmt_fmt(fmt, (PlaceholderList) {
        .elems = (Placeholder[]) {
            PLACEHOLDER_LONG("col", 26),
            PLACEHOLDER_LONG("row", 2),
            PLACEHOLDER_DOUBLE("test", 1.32122)
        },
        .elems_size = 3
    });
    printf("%s\n", res);
    free(res);
    fmt_destroy(fmt);

    free(str);
    return 0;
}

int main() {
    miniconf();
    minifmt();
    return 0;
}
