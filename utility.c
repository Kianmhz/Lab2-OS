#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>
#include <ctype.h>  // Added for isspace()
#include "myshell.h"

// Function to trim leading and trailing whitespace from input
void trim_whitespace(char *str) {
    char *end;
    while (*str == ' ') str++;  // Trim leading spaces
    if (*str == 0) return;  // Empty string

    end = str + strlen(str) - 1;
    while (end > str && *end == ' ') end--;  // Trim trailing spaces

    *(end + 1) = 0; // Null terminate
}

// Function to check if a string is empty
int is_empty(const char *str) {
    while (*str) {
        if (!isspace((unsigned char)*str)) return 0;  // Fixed implicit declaration issue
        str++;
    }
    return 1;
}

// Function to check if a command is internal
int is_internal_command(const char *cmd) {
    const char *internal_cmds[] = {"cd", "clr", "dir", "environ", "echo", "help", "pause", "quit"};
    size_t num_cmds = sizeof(internal_cmds) / sizeof(internal_cmds[0]);  // Fixed warning
    for (size_t i = 0; i < num_cmds; i++) {
        if (strcmp(cmd, internal_cmds[i]) == 0) return 1;
    }
    return 0;
}

// Function to split input string into arguments
void parse_command(char *input, char **args) {
    char *token;
    int i = 0;

    token = strtok(input, " \t\n");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;  // Null terminate the argument list
}

// Function to print an error message
void print_error(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
}
