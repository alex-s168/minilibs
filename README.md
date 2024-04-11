# minilibs
A set of simple header-only libraries for C.

## miniconf
## Example
C code:
```c++
int main() {
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
```
(If you want to get many variables in for example `status bar/normal`, you should use `config_children` and use the temporary result)

config:
```
status bar:
    visible: true
    scale: 0.4
    background: xFFFFFFFF
    normal:
        format: "{lang}  {line}/{col}
    input:
        has hint:
            format: "{hint}: {message}
        has not hint:
            format: "{message}
```
=======

## minifmt
## Dependencies
- stdlib.h: malloc, free, realloc
- math.h: pow

## Example
```c++
static const char *fmt_str = "Test {row} str {col.h}";

int main(void) {
    const size_t len = strlen(fmt_str);
    char *str = malloc(len + 1);
    memcpy(str, fmt_str, len + 1);

    const Fmt fmt = fmt_compile(str);
    char *res = fmt_fmt_fmt(fmt, (PlaceholderList) {
        .elems = (Placeholder[]) {
            PLACEHOLDER_LONG("col", 11),
            PLACEHOLDER_LONG("row", 2)
        },
        .elems_size = 2
    });
    printf("%s\n", res);
    free(res);
    fmt_destroy(fmt);

    free(str);
    return 0;
}
```

## Additional features
- `ll_to_ascii`
- `d_to_ascii`
