#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 100

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

int main(int argc, char *argv[]) {
    char input[MAX_INPUT_SIZE];

    // Set environment variable for shell
    char shell_path[MAX_INPUT_SIZE];
    if (realpath(argv[0], shell_path)) {
        setenv("shell", shell_path, 1);
    }

    if (argc == 2) {
        // Batch mode: Read commands from a file
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror("Error opening batch file");
            return 1;
        }
        while (fgets(input, sizeof(input), file)) {
            execute_command(input);
        }
        fclose(file);
        return 0;
    }

    // Interactive Mode
    while (1) {
        printf("myshell> ");
        if (!fgets(input, sizeof(input), stdin)) break;
        execute_command(input);
    }

    return 0;
}

void execute_command(char *input) {
    char *args[MAX_ARG_SIZE];
    char *token = strtok(input, " \t\n");
    int i = 0;

    while (token) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;

    if (args[0] == NULL) return;

    if (strcmp(args[0], "cd") == 0 || strcmp(args[0], "clr") == 0 || 
        strcmp(args[0], "dir") == 0 || strcmp(args[0], "environ") == 0 || 
        strcmp(args[0], "echo") == 0 || strcmp(args[0], "help") == 0 || 
        strcmp(args[0], "pause") == 0 || strcmp(args[0], "quit") == 0) {
        execute_internal_command(args);
    } else {
        execute_external_command(args);
    }
}

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
        exit(0);
    }
}

void change_directory(char *path) {
    if (!path) {
        printf("%s\n", getenv("PWD"));
    } else if (chdir(path) == 0) {
        setenv("PWD", path, 1);
    } else {
        perror("cd failed");
    }
}

void clear_screen() {
    printf("\033[H\033[J");
}

void list_directory(char *path) {
    struct dirent *entry;
    DIR *dir = opendir(path ? path : ".");
    if (!dir) {
        perror("dir failed");
        return;
    }
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
}

void show_environment() {
    extern char **environ;
    for (char **env = environ; *env; env++) {
        printf("%s\n", *env);
    }
}

void echo_command(char **args) {
    for (int i = 1; args[i]; i++) {
        printf("%s ", args[i]);
    }
    printf("\n");
}

void display_help() {
    system("more readme");
}

void pause_shell() {
    printf("Press Enter to continue...");
    while (getchar() != '\n');
}

void execute_external_command(char **args) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
    } else if (pid == 0) {
        setenv("parent", getenv("shell"), 1);
        execvp(args[0], args);
        perror("Command execution failed");
        exit(1);
    } else {
        wait(NULL);
    }
}
