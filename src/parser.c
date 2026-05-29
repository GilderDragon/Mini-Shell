#include "parser.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

char *read_line(void) {
  char line[MAX_LINE];

  printf("%s", get_prompt());
  fflush(stdout);

  if (!fgets(line, MAX_LINE, stdin)) {
    return NULL;
  }

  line[strcspn(line, "\n")] = '\0';
  return strdup(line);
}

char **parse_line(char *line) {
  if (!line)
    return NULL;

  int capacity = 16;
  char **args = malloc(capacity * sizeof(char *));
  if (!args)
    return NULL;

  int position = 0;
  const char *token = strtok(line, " \t\r\n");

  while (token) {
    if (position >= capacity - 1) {
      capacity *= 2;
      args = realloc(args, capacity * sizeof(char *));
      if (!args)
        return NULL;
    }

    args[position] = strdup(token);
    position++;

    token = strtok(NULL, " \t\r\n");
  }

  args[position] = NULL;
  return args;
}

void free_args(char **args) {
  if (!args)
    return;
  for (int i = 0; args[i] != NULL; i++) {
    free(args[i]);
  }
  free(args);
}
