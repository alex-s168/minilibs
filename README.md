# minilibs
A set of simple header-only libraries for C.

## minitab
Simple string table printing library for C.

### Example
```c++
int main() {
    Table table;
    table.cols = 3;
    table.rows = 3;
    table_create(&table);

    table_color_col(table, ANSI_COLOR_RED, 0);

    table.colsExtraPad[1] = 2;
    table.colsPadLeft[1] = true;

    table_cell(table, 0, 0).text = "Test";

    table_put_fmt(table, 1, 0, "Test %i", 1);
    table_cell(table, 1, 0).color = ANSI_COLOR_GREEN;

    table_print(table, stdout);
    table_delete(&table);
}
```

## miniconf
Simple configuration file parser for C.

### Example
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
Simple string templating library for C.

### Dependencies
- stdlib.h: malloc, free, realloc
- math.h: pow

### Example
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

### Additional features
- `ll_to_ascii`
- `d_to_ascii`
