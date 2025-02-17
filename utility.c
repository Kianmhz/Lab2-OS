// Include standard libraries for I/O, string handling, process management, directory operations, and error handling
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>
#include <ctype.h>  // Required for the isspace() function

#include "myshell.h"  // Include the header file for function prototypes

/**
 * Trims leading and trailing whitespace from a string.
 * @param str The input string to modify.
 */
void trim_whitespace(char *str) {
    char *end;

    // Move pointer forward while there are leading spaces
    while (*str == ' ') str++;  
    
    // If the string is empty after trimming spaces, return
    if (*str == 0) return;  

    // Move to the end of the string and backtrack to remove trailing spaces
    end = str + strlen(str) - 1;
    while (end > str && *end == ' ') end--;  

    *(end + 1) = 0; // Null terminate the trimmed string
}

/**
 * Checks if a string is empty (contains only whitespace).
 * @param str The input string.
 * @return 1 if the string is empty, 0 otherwise.
 */
int is_empty(const char *str) {
    while (*str) {  
        if (!isspace((unsigned char)*str)) return 0;  // If any non-space character is found, return 0
        str++;  
    }
    return 1;  // If only spaces were found, return 1 (true)
}

/**
 * Checks if a command is a built-in shell command.
 * @param cmd The command string to check.
 * @return 1 if the command is built-in, 0 otherwise.
 */
int is_internal_command(const char *cmd) {
    // List of built-in commands
    const char *internal_cmds[] = {"cd", "clr", "dir", "environ", "echo", "help", "pause", "quit"};

    // Calculate the number of built-in commands
    size_t num_cmds = sizeof(internal_cmds) / sizeof(internal_cmds[0]);  

    // Check if the command matches any built-in command
    for (size_t i = 0; i < num_cmds; i++) {
        if (strcmp(cmd, internal_cmds[i]) == 0) return 1;  // Match found, return true
    }
    return 0;  // Not a built-in command
}

/**
 * Parses a command string into an array of arguments.
 * @param input The raw input string.
 * @param args The array where parsed arguments will be stored.
 */
void parse_command(char *input, char **args) {
    char *token;
    int i = 0;

    // Tokenize the input using space, tab, and newline as delimiters
    token = strtok(input, " \t\n");
    while (token != NULL) {
        args[i++] = token;  // Store each token in the args array
        token = strtok(NULL, " \t\n");  // Get next token
    }
    args[i] = NULL;  // Null terminate the argument list
}

/**
 * Prints an error message to standard error output.
 * @param msg The error message to display.
 */
void print_error(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);  // Print error message to stderr
}
