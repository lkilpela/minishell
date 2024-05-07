## In Collaboration with Allar Klein
<h1 align="center">
	<img src="https://github.com/lkilpela/42-project-badges/blob/main/badges/minishelle.png" />
    <b><i>A Mini Recreation of Bash</i></b><br>

</h1>

## About The Project

Minishell is a simple, mini shell implemented in C. It provides a command line user interface for Unix-like operating systems.

### Requirements
- Display a prompt when waiting for a new command
- Have a working history
- Search and launch the right executable (based on the PATH variable or using a relative or an absolute path)
- Avoid using more than one global variable to indicate a received signal
- Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon)
- Handle ’ (single quote) and " (double quote) in command input
- Implement redirections:
	- `<` redirect input
	- `>` redirect output
 	- `<<` for input until a delimiter (heredoc)
  	- `>>` for output in append mode
- Implement pipes (`|`)
- Handle environment variables (`$` followed by a sequence of characters)
- Handle `$?` which should expand to the exit status of the most recently executed foreground pipeline
- Handle `ctrl-C`, `ctrl-D` and `ctrl-\` which should behave like in bash
- Implement the following builtins: 
    - `echo` with option `-n`
    - `cd` with only a relative or absolute path
    - `pwd` with no options
    - `export` with no options
    - `unset` with no options
    - `env` with no options or arguments
    - `exit` with no options
 
🚫 No Implementation Needed
- && and ||
- wildcards
- special symbols that were not specifically asked for

## Implementation

### Builtins

### External functions

- `readline`: Reads a line from the terminal and returns it.
- `rl_clear_history`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`, `add_history` Functions from the readline library used to manipulate the command line history.
- `printf`: Prints formatted output to stdout.
- `malloc, free`: Functions for dynamic memory allocation.
- `write`: Writes data to a file descriptor.
- `access`: Checks the accessibility of a file.
- `open, read, close`: Functions to open, read from, and close a file.
- `fork`: Creates a new process by duplicating the existing process.
- `wait, waitpid, wait3, wait4`: Functions to make a process wait until its child processes stop or terminate.
- `signal, sigaction, sigemptyset, sigaddset, kill`: Functions for handling signals.
- `exit`: Terminates a process.
- `getcwd, chdir`: Functions to get and change the current working directory.
- `stat, lstat, fstat`: Functions to get file status.
- `unlink`: Deletes a name from the filesystem.
- `execve`: Executes a program.
- `dup, dup2`: Functions to duplicate a file descriptor.
- `pipe`: Creates a pipe.
- `opendir, readdir, closedir`: Functions to open, read from, and close a directory.
- `strerror, perror`: Functions to handle errors.
- `isatty, ttyname, ttyslot, ioctl`: Functions for handling terminal I/O.
- `getenv`: Gets an environment variable.
-  `tcsetattr, tcgetattr`: Functions to get and set terminal attributes.
- `tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs`: Functions from the termcap library used for terminal handling.

## Resources

1. https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
2. https://github.com/Swoorup/mysh
3. Shell syntax: https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html
4. https://minishell.simple.ink/


<!--
<p align="center">
    <img alt="score" src="https://img.shields.io/badge/score-0%2F100-brightgreen" />
<p align="center">
    <img alt="group" src="https://img.shields.io/badge/group-yellow" />
    <img alt="estimated time" src="https://img.shields.io/badge/estimation-210%20hours-blue" />
    <img alt="XP earned" src="https://img.shields.io/badge/XP-2814-orange" />
<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/lkilpela/pipex?color=lightblue" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/lkilpela/philosophers?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/lkilpela/philosophers?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/lkilpela/philosophers?color=green" />
</p> -->
