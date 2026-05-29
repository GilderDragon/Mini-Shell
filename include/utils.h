#ifndef MINI_SHELL_UTILS_H
#define MINI_SHELL_UTILS_H

char *get_prompt(void);

char *tilde_expand(const char *path);

int print_colored(const char *text, const char *color);

#endif // MINI_SHELL_UTILS_H