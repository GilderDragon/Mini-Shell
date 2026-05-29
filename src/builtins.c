#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "builtins.h"
#include "utils.h"

builtin_func_t builtins[] = {{"help", &shell_help},
                             {"exit", &shell_exit},
                             {"cd", &shell_cd},
                             {"pwd", &shell_pwd}};

int shell_help(char **args) {
    printf("Simplified shell version\n");
    printf("Built-in commands:\n");

    for (int i = 0; i < count_builtins(); i++) {
        printf("%s\n", builtins[i].name);
    }

    return 0;
}

int shell_exit(char **args) { return EXIT; }

int shell_cd(char **args) {
    const char *path = args[1];

    if (!path) {
        path = getenv("HOME");
        if (!path) {
            fprintf(stderr, "shell: Invalid argument\n");
            return EINVAL;
        }
    } else {
        path = tilde_expand(args[1]);
        if (!path) {
            fprintf(stderr, "shell: Invalid argument\n");
            return EINVAL;
        }
    }

    if (chdir(path) != 0) {
        perror("shell");
        return errno;
    }

    return 0;
}

int shell_pwd(char **args) {
    char pwd[1024];

    if (getcwd(pwd, sizeof(pwd)) != NULL) {
        printf("%s\n", pwd);
        return 0;
    }

    perror("shell");
    return errno;
}

int count_builtins(void) { return sizeof(builtins) / sizeof(builtins[0]); }
