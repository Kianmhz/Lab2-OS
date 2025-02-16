#ifndef MYSHELL_H
#define MYSHELL_H

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 100

void trim_whitespace(char *str);
int is_empty(const char *str);
int is_internal_command(const char *cmd);
void parse_command(char *input, char **args);
void print_error(const char *msg);

#endif
