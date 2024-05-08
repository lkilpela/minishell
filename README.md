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
- Handle `’` (single quote) and `"`(double quote) in command input
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

🚫 Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon)

### ⭐ BONUS
- && and || and parenthesis
- wildcards

## step_by_step

* Prompt implementation
* Tokenizer implementation
* Variables expansion implementation
* Builtins implementation
* Parse and execute system design
* Signals implementation
* Parsing implementation
* Execute implementation
* Norm
* Bugs hunting

### Mindmap

![mindmap](https://github.com/lkilpela/minishell/blob/main/doc/Mind%20Maps%20.jpg))

### External functions
<details>
  <summary>Click to expand </summary>

| Name | Description |
| --- | --- |
| `libft` | A library of reproduction standard C library functions.|
| `readline` | Reads a line from the terminal and returns it.|
| `rl_clear_history`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`, `add_history` | Functions from the readline library used to manipulate the command line history.|
| `printf`| Prints formatted output to stdout.|
| `malloc, free`| Functions for dynamic memory allocation.|
| `write`| Writes data to a file descriptor.|
| `access`| Checks the accessibility of a file.|
| `open, read, close`| Functions to open, read from, and close a file.|
| `fork`| Creates a new process by duplicating the existing process.|
| `wait, waitpid, wait3, wait4`| Functions to make a process wait until its child processes stop or terminate.|
| `signal, sigaction, sigemptyset, sigaddset, kill`| Functions for handling signals.|
| `exit`| Terminates a process.|
| `getcwd, chdir`| Functions to get and change the current working directory.|
| `stat, lstat, fstat`| Functions to get file status.|
| `unlink`| Deletes a name from the filesystem.|
| `execve`| Executes a program.|
| `dup, dup2`| Functions to duplicate a file descriptor.|
| `pipe`| Creates a pipe.|
| `opendir, readdir, closedir`| Functions to open, read from, and close a directory.|
| `strerror, perror`| Functions to handle errors.|
| `isatty, ttyname, ttyslot, ioctl`| Functions for handling terminal I/O.|
| `getenv`| Gets an environment variable.|
| `tcsetattr, tcgetattr`| Functions to get and set terminal attributes.|
| `tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs`| Functions from the termcap library used for terminal handling.|
	
</details>

## Resources

### unix
1. [Writing Your Own Shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
2. [Unix Processes in C -video](https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY)
3. [Shell syntax](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)
4. [Termination Signals](https://www.gnu.org/software/libc/manual/html_node/Termination-Signals.html)
5. [Bash Guide for Beginners](https://tldp.org/LDP/Bash-Beginners-Guide/html/index.html)
6. [Programming Terminal Devices -video](https://www.youtube.com/watch?v=t5sC6G73oo4)
7. [Introduction to System Programming -video](https://www.youtube.com/watch?v=qThI-U34KYs&list=PL7B2bn3G_wfC-mRpG7cxJMnGWdPAQTViW)
8. [Capturing exit status code of child process](https://stackoverflow.com/questions/27306764/capturing-exit-status-code-of-child-process)
9. [Notion with details about Readline lib, Termcaps and Signals](https://www.notion.so/Minishell-e856e9af377f44b588e5fe120d4b6e2a)
10. [Bash Manual](https://www.gnu.org/software/bash/manual/bash.html)

### hashtable
* [Hash Table in C/C++ – A Complete Implementation](https://www.journaldev.com/35238/hash-table-in-c-plus-plus)

### tokenizer
* [Lexical Analysis](https://en.wikipedia.org/wiki/Lexical_analysis)

### more
* [Notion with tons of materials](https://www.notion.so/Minishell-Materials-7bbd45a806e04395ab578ca3f805806c)

## References
1. [Swoorup/mysh](https://github.com/Swoorup/mysh)
2. [maiadegraaf/minishell](https://github.com/maiadegraaf/minishell)
3. [LucasKuhn/minishell_tester](https://github.com/LucasKuhn/minishell_tester)
4. [vportens/minishell](https://github.com/vportens/minishell)
5. [paulahemsi/minishell](https://github.com/paulahemsi/minishell)
6. [madebypixel02/minishell](https://github.com/madebypixel02/minishell?tab=readme-ov-file)

