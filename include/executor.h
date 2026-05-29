#ifndef MINI_SHELL_EXECUTOR_H
#define MINI_SHELL_EXECUTOR_H

#define NOT_FOUND (-2)

int execute_command(char **args);

int execute_builtin(char **args);

int execute_external(char **args);

#endif // MINI_SHELL_EXECUTOR_H
