#include "utils.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>

char *get_prompt(void) {
    static char prompt[1024];
    char cwd[512];

    if (!getcwd(cwd, sizeof(cwd))) {
        strcpy(cwd, "?");
    }

    snprintf(prompt, sizeof(prompt), "\033[1;32miu7-shell\033[0m:>\033[1;34m%s\033[0m> ", cwd);

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
    return printf("%s%s\033[0m", color, text);
}
