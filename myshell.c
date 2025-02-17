// Include standard C libraries for input/output, process handling, and file operations
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>

// Define constants for buffer sizes
#define MAX_INPUT_SIZE 1024  // Maximum input length for commands
#define MAX_ARG_SIZE 100      // Maximum number of arguments per command

// Function declarations
void execute_command(char *input);
void execute_internal_command(char **args);
void execute_external_command(char **args);
void change_directory(char *path);
void clear_screen();
void list_directory(char *path);
void show_environment();
void echo_command(char **args);
void display_help();
void pause_shell();

/**
 * Main function: Initializes the shell and handles user input.
 */
int main(int argc, char *argv[]) {
    char input[MAX_INPUT_SIZE];  // Buffer for storing user input

    // Set environment variable for shell
    char shell_path[MAX_INPUT_SIZE];
    if (realpath(argv[0], shell_path)) {  // Get absolute path of the shell executable
        setenv("shell", shell_path, 1);   // Store it in environment variable "shell"
    }

    // If a batch file is provided, read and execute commands from it
    if (argc == 2) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror("Error opening batch file");  // Print error if file cannot be opened
            return 1;
        }
        while (fgets(input, sizeof(input), file)) {  // Read each line from the file
            execute_command(input);  // Execute each command
        }
        fclose(file);  // Close the batch file
        return 0;
    }

    // Interactive Mode: Loop to continuously accept user input
    while (1) {
        printf("myshell> ");  // Display the shell prompt
        if (!fgets(input, sizeof(input), stdin)) break;  // Read input, exit if EOF
        execute_command(input);  // Execute the command
    }

    return 0;
}

/**
 * Parses and executes a command.
 */
void execute_command(char *input) {
    char *args[MAX_ARG_SIZE];  // Array to store command arguments
    char *token = strtok(input, " \t\n");  // Tokenize input by spaces and newlines
    int i = 0;

    while (token) {  // Loop to extract all tokens
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;  // Null-terminate the argument array

    if (args[0] == NULL) return;  // If no command entered, do nothing

    // Check if the command is a built-in shell command
    if (strcmp(args[0], "cd") == 0 || strcmp(args[0], "clr") == 0 || 
        strcmp(args[0], "dir") == 0 || strcmp(args[0], "environ") == 0 || 
        strcmp(args[0], "echo") == 0 || strcmp(args[0], "help") == 0 || 
        strcmp(args[0], "pause") == 0 || strcmp(args[0], "quit") == 0) {
        execute_internal_command(args);
    } else {
        execute_external_command(args);  // Otherwise, run it as an external command
    }
}

/**
 * Executes built-in shell commands.
 */
void execute_internal_command(char **args) {
    if (strcmp(args[0], "cd") == 0) {
        change_directory(args[1]);
    } else if (strcmp(args[0], "clr") == 0) {
        clear_screen();
    } else if (strcmp(args[0], "dir") == 0) {
        list_directory(args[1]);
    } else if (strcmp(args[0], "environ") == 0) {
        show_environment();
    } else if (strcmp(args[0], "echo") == 0) {
        echo_command(args);
    } else if (strcmp(args[0], "help") == 0) {
        display_help();
    } else if (strcmp(args[0], "pause") == 0) {
        pause_shell();
    } else if (strcmp(args[0], "quit") == 0) {
        exit(0);  // Exit the shell
    }
}

/**
 * Changes the current working directory.
 */
void change_directory(char *path) {
    if (!path) {
        printf("%s\n", getenv("PWD"));  // Print current directory if no path is given
    } else if (chdir(path) == 0) {  // Change directory
        setenv("PWD", path, 1);  // Update the PWD environment variable
    } else {
        perror("cd failed");  // Print error if directory change fails
    }
}

/**
 * Clears the terminal screen.
 */
void clear_screen() {
    printf("\033[H\033[J");  // ANSI escape sequence to clear screen
}

/**
 * Lists the contents of a directory.
 */
void list_directory(char *path) {
    struct dirent *entry;
    DIR *dir = opendir(path ? path : ".");  // Open directory (default: current directory)
    if (!dir) {
        perror("dir failed");  // Print error if directory cannot be opened
        return;
    }
    while ((entry = readdir(dir)) != NULL) {  // Read each directory entry
        printf("%s\n", entry->d_name);  // Print entry name
    }
    closedir(dir);  // Close directory
}

/**
 * Displays all environment variables.
 */
void show_environment() {
    extern char **environ;
    for (char **env = environ; *env; env++) {
        printf("%s\n", *env);  // Print each environment variable
    }
}

/**
 * Prints a message to the screen.
 */
void echo_command(char **args) {
    for (int i = 1; args[i]; i++) {
        printf("%s ", args[i]);  // Print each word with a space
    }
    printf("\n");
}

/**
 * Displays the shell's help documentation.
 */
void display_help() {
    system("more README.md");  // Display README.md file using 'more'
}

/**
 * Pauses the shell until the user presses Enter.
 */
void pause_shell() {
    printf("Press Enter to continue...");
    while (getchar() != '\n');  // Wait for Enter key press
}

/**
 * Executes an external command by forking a new process.
 */
void execute_external_command(char **args) {
    pid_t pid = fork();  // Create a new process
    if (pid < 0) {
        perror("Fork failed");  // Error in forking
    } else if (pid == 0) {  // Child process
        setenv("parent", getenv("shell"), 1);  // Set "parent" environment variable
        execvp(args[0], args);  // Execute external command
        perror("Command execution failed");  // Print error if execvp() fails
        exit(1);  // Exit child process
    } else {
        wait(NULL);  // Parent waits for child process to finish
    }
}
