MYSHELL USER MANUAL

Introduction:
This is a simple shell implementation named 'myshell'. It supports internal commands and execution of external programs.

Usage:
1. Run the shell: `./myshell`
2. Execute commands interactively or via batch file: `./myshell batchfile`

Supported Internal Commands:
- `cd <directory>`: Change the current directory.
- `clr`: Clear the screen.
- `dir <directory>`: List contents of a directory.
- `environ`: Print environment variables.
- `echo <message>`: Print a message.
- `help`: Show this manual.
- `pause`: Wait for user input.
- `quit`: Exit the shell.

External Commands:
- Any other command is executed as a separate process.

Batch Mode:
- Provide a file as an argument to execute commands from it automatically.

Compilation:
- Run `make` to compile the shell.
- Run `make clean` to remove the executable.

Enjoy using myshell!
