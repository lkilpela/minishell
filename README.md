<h1 align="center">
	<img src="https://github.com/lkilpela/42-project-badges/blob/main/badges/minishelle.png" />

</h1>

<p align="center">
	<b><i>A Minimalistic Shell Implementation in C</i></b><br>
</p>

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
</p>

## About The Project

Minishell is a simple, minimalistic shell implemented in C. It provides a command line user interface for Unix-like operating systems.

### Requirements
- Display a prompt when waiting for a new command
- Have a working history
- Search and launch the right executable (based on the PATH variable or using a relative or an absolute path)
- Avoid using more than one global variable to indicate a received signal
- Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon)
- Handle ’ (single quote) and " (double quote) in command input
- Implement redirections: `<` for input, `>` for output, `<<` for input until a delimiter, `>>` for output in append mode
- Implement pipes (`|`)
- Handle environment variables (`$` followed by a sequence of characters)
- Handle `$?` which should expand to the exit status of the most recently executed foreground pipeline
- Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash
- Implement the following builtins: `echo` with option `-n`, `cd` with only a relative or absolute path, `pwd` with no options, `export` with no options, `unset` with no options, `env` with no options or arguments, `exit` with no options