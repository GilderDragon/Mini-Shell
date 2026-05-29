#include "utils.h"

#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *get_prompt(void) {
    static char prompt[1024];
    char cwd[512];
    const char *display_path = cwd;

    char username[256] = "user";
    char hostname[256] = "host";

    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);
    if (pw && pw->pw_name) {
        snprintf(username, sizeof(username), "%s", pw->pw_name);
    }

    if (gethostname(hostname, sizeof(hostname))) {
        strcpy(hostname, "host");
    }

    if (!getcwd(cwd, sizeof(cwd))) {
        strcpy(cwd, "?");
    } else {
        const char *home = getenv("HOME");
        if (!home && pw) {
            home = pw->pw_dir;
        }

        if (home) {
            const size_t home_len = strlen(home);

            if (strncmp(cwd, home, home_len) == 0) {
                if (cwd[home_len] == '\0' || cwd[home_len] == '/') {
                    static char tilde_path[512];
                    snprintf(tilde_path, sizeof(tilde_path), "~%s",
                             cwd + home_len);
                    display_path = tilde_path;
                }
            }
        }
    }

    const char sign = uid == 0 ? '#' : '$';

    snprintf(prompt, sizeof(prompt),
             "\033[1;32m%s@%s\033[0m:\033[1;34m%s\033[0m%c ", username,
             hostname, display_path, sign);

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
    if (!expanded)
        return NULL;

    strcpy(expanded, home);
    strcat(expanded, path + 1);

    return expanded;
}

int print_colored(const char *text, const char *color) {
    return printf("%s%s\033[0m", color, text);
}
