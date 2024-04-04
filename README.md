# miniconf
Simple, minimal, header-only platform-independent C configuration library.

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