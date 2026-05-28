#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "builtin_functions.h"

builtin_func_t builtins[] = {
    {"help", &shell_help,},
    {"exit", &shell_exit,},
    {"cd", &shell_cd,},
    {"pwd", &shell_pwd,}
};

int shell_help(char **args) {
    printf("Упрощенная версия shell\n");
    printf("Встроенные команды:\n");

    for (int i = 0; i < count_builtins(); i++) {
        printf("%s\n", builtins[i].name);
    }

    return 0;
}

int shell_exit(char **args) {
    return EXIT;
}

int shell_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "shell: Invalid argument\n");
    }

    if (chdir(args[1]) != 0) {
        perror("shell");
    }

    return 0;
}

int shell_pwd(char **args) {
    char *pwd = getenv("PWD");
    if (pwd == NULL) {
        perror("shell");
    }

    printf("%s\n", pwd);

    return 0;
}

int count_builtins(void) {
    return sizeof(builtins) / sizeof(builtins[0]);
}
