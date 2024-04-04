/*

status bar:
    visible: true
    scale: 0.4
    background: xFFFFFFFF
    ?normal:
        format: "{lang}  {line}/{col}
    ?input:
        ?has hint:
            format: "{hint}: {message}
        ?!has hint:
            format: "{message}

 */

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char  **lines;
    size_t        lines_len;
} Config;

static void config_init(Config *config) {
    config->lines = NULL;
    config->lines_len = 0;
}

static void config_destroy(Config *config) {
    free(config->lines);
    config->lines = NULL;
    config->lines_len = 0;
}

static void config_add_line(Config *dest, const char *line) {
    dest->lines = realloc(dest->lines, (dest->lines_len + 1) * sizeof (char *));
    dest->lines[dest->lines_len ++] = line;
}

static void config_add_all_lines_adv(Config *dest,
                                     const Config src,
                                     const size_t start_line,
                                     const size_t end_line,
                                     const size_t indent)
{
    for (size_t i = start_line; i <= end_line; i ++) {
        config_add_line(dest, src.lines[i] + indent);
    }
}

static void config_add_all_lines(Config *dest, const Config src) {
    if (src.lines_len == 0)
        return;
    config_add_all_lines_adv(dest, src, 0, src.lines_len - 1, 0);
}

typedef struct {
    const char *name;
} ConfigParam;

typedef struct {
    ConfigParam *params;
    size_t       len;
} ConfigParams;

static void configparams_init(ConfigParams *params) {
    params->params = NULL;
    params->len = 0;
}

static void configparams_destroy(ConfigParams *params) {
    if (params->params)
        free(params->params);
    params->params = NULL;
    params->len = 0;
}

void configparams_add_all(ConfigParams *dest, const ConfigParams src) {
    const size_t oldLen = dest->len;
    dest->len = oldLen + src.len;
    dest->params = realloc(dest->params, sizeof(ConfigParam) * dest->len);
    memcpy(dest->params + oldLen, src.params, sizeof(ConfigParam) * src.len);
}

void configparams_add(ConfigParams *dest, ConfigParam param) {
    configparams_add_all(dest, (ConfigParams) { .len = 1, .params = &param });
}

void config_child(Config *dest,
                  const Config cfg,
                  const char *child,
                  ConfigParams params, // TODO: implement
                  bool *is_found)
{
    bool found = false;
    size_t start_line = 0;
    for (size_t i = 0; i < cfg.lines_len; i ++) {
        const char *line = cfg.lines[i];
        if (line[0] == ' ') // higher indent
            continue;

        const char *col = strchr(line, ':');
        const size_t len = col - line;

        if (memcmp(child, line, len) != 0)
            continue;

        if (child[len] != '\0')
            continue;

        start_line = i;
        found = true;
        break;
    }
    if (!found)
        return;
    *is_found = found;

    size_t end_line = 0;
    for (size_t i = start_line + 1; i < cfg.lines_len; i ++) {
        const char *line = cfg.lines[i];
        if (line[0] == ' ') // higher indent
            end_line ++;
        else
            break;
    }

    config_add_all_lines_adv(dest, cfg, start_line, end_line, 4);
}

typedef enum {
    ConfigType_LONG,
    ConfigType_DOUBLE,
    ConfigType_BOOL,
    ConfigType_STRING,

    ConfigType_BLOCK,
    ConfigType_INVALID,
} ConfigType;

ConfigType config_type(const Config cfg) {

}

long config_get_long(const Config cfg, bool *ok) {

}

double config_get_double(const Config cfg, bool *ok) {

}

bool config_get_bool(const Config cfg, bool *ok) {

}

const char *config_get_str(const Config cfg, bool *ok) {

}