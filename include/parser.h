#ifndef MINI_SHELL_PARSER_H
#define MINI_SHELL_PARSER_H

char *read_line(void);

char **parse_line(char *line);

void free_args(char **args);

#endif //MINI_SHELL_PARSER_H
