#include "shell.h"

#include <stdio.h>
#include <stdlib.h>

#include "builtins.h"
#include "executor.h"
#include "parser.h"

void shell_loop(void) {
    int status = 0;

    printf("=== Mini-Shell v0.1 ===\n");
    printf("Type 'help' for available commands. Ctrl+D to exit\n\n");

    while (status != EXIT) {
        char *line = read_line();
        if (!line) {
            printf("\n");
            break;
        }

        char **args = parse_line(line);
        if (args && args[0]) {
            status = execute_command(args);
        }

        free_args(args);
        free(line);
    }

    printf("Mini-Shell exited\n");
}
