#include "executor.h"
#include "builtins.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int execute_command(char **args) {

    if (args[0] == NULL) {
        return 0;
    }

    const int rc = execute_builtin(args);

    if (rc == EXIT) {
        exit(EXIT);
    }

    if (rc == NOT_FOUND) {
        return execute_external(args);
    }

    return rc;
}

int execute_builtin(char **args) {
    for (int i = 0; i < count_builtins(); i++) {
        if (strcmp(args[0], builtins[i].name) == 0) {
            return builtins[i].func(args);
        }
    }

    return NOT_FOUND;
}

int execute_external(char **args) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("shell");
        return errno;
    }

    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("shell");
            exit(EXIT_FAILURE);
        }
    }

    int status;
    if (waitpid(pid, &status, 0) == -1) {
        perror("shell");
        return errno;
    }

    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }

    return 0;
}
