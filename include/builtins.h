#ifndef MINI_SHELL_BUILTINS_H
#define MINI_SHELL_BUILTINS_H

#define EXIT (-1)

typedef struct {
    const char *name;
    int (*func)(char **args);
} builtin_func_t;

extern builtin_func_t builtins[];

int shell_help(char **args);

int shell_exit(char **args);

int shell_cd(char **args);

int shell_pwd(char **args);

int count_builtins(void);

#endif //MINI_SHELL_BUILTINS_H
