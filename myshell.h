#ifndef MYSHELL_H  // Include guard to prevent multiple inclusions of this header file
#define MYSHELL_H  

// Define constants for buffer sizes
#define MAX_INPUT_SIZE 1024  // Maximum length of user input
#define MAX_ARG_SIZE 100      // Maximum number of arguments a command can have

/**
 * Trims leading and trailing whitespace from a string.
 * @param str The input string to be modified.
 */
void trim_whitespace(char *str);

/**
 * Checks if a string is empty (i.e., contains only whitespace).
 * @param str The input string.
 * @return 1 if the string is empty, 0 otherwise.
 */
int is_empty(const char *str);

/**
 * Checks if a given command is a built-in shell command.
 * @param cmd The command string to check.
 * @return 1 if the command is built-in, 0 otherwise.
 */
int is_internal_command(const char *cmd);

/**
 * Parses a command string into an array of arguments.
 * @param input The raw input string.
 * @param args The array where parsed arguments will be stored.
 */
void parse_command(char *input, char **args);

/**
 * Prints an error message to standard error output.
 * @param msg The error message to be displayed.
 */
void print_error(const char *msg);

#endif  // End of include guard
