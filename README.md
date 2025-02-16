# MyShell - A Simple Command Line Interpreter

MyShell is a Unix-based shell that supports built-in commands and executes external programs. It works in both **interactive mode** (user input) and **batch mode** (reading commands from a file). 

## Compilation & Execution
To compile the shell, run `make`. To clean compiled files, run `make clean`.  
To start MyShell interactively, run `./myshell`.  
To execute commands from a file, use `./myshell batchfile`.

## Built-in Commands
- `cd <directory>`: Change the working directory. Prints current directory if no argument is given.
- `clr`: Clears the screen.
- `dir <directory>`: Lists files in the specified directory.
- `environ`: Prints all environment variables.
- `echo <message>`: Displays text on the screen.
- `help`: Shows this `readme` file.
- `pause`: Waits for the user to press `Enter` before continuing.
- `quit`: Exits the shell.

## Executing External Commands
Any command that is not built-in runs as an external program. Examples:  
`ls -l`, `gcc --version`, `ping google.com`.  

## Batch Mode Example
Create a file (`commands.txt`) with a list of commands, e.g.:
```
cd /home/user
dir
echo Running scripts
quit
```
Run it using `./myshell commands.txt`.

## Notes
- Environment variables: `shell` (stores the path of `myshell`), `parent` (tracks execution).
- No support for pipes (`|`) or background processes (`&`).
- Only text-based batch files are supported.
