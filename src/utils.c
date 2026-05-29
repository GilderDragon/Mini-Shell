#include "utils.h"

#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>

#define COLOR_GREEN "\033[1;32m"
#define COLOR_BLUE "\033[1;34m"
#define COLOR_RESET "\033[0m"

char *get_prompt(void) {
    static char prompt[1024];
    char cwd[512];

    if (!getcwd(cwd, sizeof(cwd))) {
        strcpy(cwd, "?");
    }

    snprintf(prompt, sizeof(prompt), "%siu7-shell:%s> %s", COLOR_GREEN, COLOR_RESET, cwd);

    return prompt;
}

char *tilde_expand(const char *path) {
    if (!path || path[0] != '~') {
        return strdup(path ? path : "");
    }

    const char *home = getenv("HOME");
    if (!home) {
        struct passwd *pw = getpwuid(getuid());
        home = pw ? pw->pw_dir : "/";
    }

    char *expanded = malloc(strlen(path) + strlen(home) + 1);
    if (!expanded) return NULL;

    strcpy(expanded, home);
    strcat(expanded, path + 1);

    return expanded;
}

int print_colored(const char *text, const char *color) {
    return printf("%s%s%s", color, text, COLOR_RESET);
}
