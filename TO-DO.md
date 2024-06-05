# To-Do List

## signals
- [ ] signal handling in child process.
- [ ] signal handling in heredoc.
- [ ] probably more signal stuff.

## validate
- [ ] split validate_command into smaller functions

## parse
- [ ] in case of mutlple infiles when one file is invalid, it should NULL the command. (probably need to move file opening to parser then)
- [ ] simple_cmd and maybe parser function refactor for readability and simplicity

## exec
- [ ] make in our minishell does not work, not sure why
- [ ] updated variables to be sent to the execve
- [ ] bash has exit code `0` vs minishell has exit code `139`
```
minishell$ $EMPTY
minishell$ echo $?
139
```
- [ ] Minishell's ouput is missing `-`

echo - "" "  " hello

expected output: `- <empty>    hello`
```
minishell$ echo - "" "  " hello
a_token_value: echo                 a_token_type: WORD
a_token_value: -                    a_token_type: WORD
a_token_value: ""                   a_token_type: WORD
a_token_value: "  "                 a_token_type: WORD
a_token_value: hello                a_token_type: WORD
Command 1:
Input redirection: (null)
Output redirection: (null)
Command: echo
Args (5): <echo> <-> <> <  > <hello> 
    hellominishell$ 
```

- [x] SEGFAULT
minishell$ doesntexist
minishell: doesntexist: command not found
minishell$ $EMPTY
zsh: segmentation fault  ./minishell
https://github.com/lkilpela/minishell/commit/9ca9fad2ad6d794c093847263293970c69d47c00

## builtins
- [ ] update $OLDPWD and $PWD env variables when using 'cd'.
- [ ] update $SHLVL properly

## NORM

child.c: Error!
Error: TOO_MANY_LINES       (line:  84, col:   1):      Function has more than 25 lines

2. Tokenizer
token_list.c: Error!
Error: TOO_MANY_LINES       (line:  46, col:   1):      Function has more than 25 lines

3. Parser
parser_utils.c: Error!
Error: TOO_MANY_FUNCS       (line:  96, col:   1):      Too many functions in file
- UNUSED FUNC: void	clear_token_quotes(t_token_list *t)

4. Error
errors.c: Error!
Error: TOO_MANY_FUNCS       (line: 101, col:   1):      Too many functions in file
Error: TOO_MANY_FUNCS       (line: 120, col:   1):      Too many functions in file
Error: TOO_MANY_FUNCS       (line: 131, col:   1):      Too many functions in file
Error: TOO_MANY_FUNCS       (line: 148, col:   1):      Too many functions in file
Error: TOO_MANY_FUNCS       (line: 164, col:   1):      Too many functions in file

lalloc.c: Error!
Error: TOO_MANY_FUNCS       (line:  65, col:   1):      Too many functions in file
Error: TOO_MANY_FUNCS       (line:  77, col:   1):      Too many functions in file

5. Builtins
waiting for cleaning up

6. env_var
waiting for cleaning up



#DONE

## validate
- [x] "$HOME here '$HOME' test": expanded single word with enclosed quotes. Print: minishell: /Users/lumik here '/Users/lumik' test: No such file or directory

- [x] "$HOME": expanded single word with enclosed quotes.
Print: minishell: /Users/lumik: is a directory

- [x] "$HOME" here: two words, expanded var & arg here
Print: minishell: /Users/lumik: is a directory

- [x] validate command is a directory, error msg: bash is showing cmd not executable for this, which makes sense, so error code `E_CODE_CND_NEXEC = 126`
- [x] validate command is not existed, error msg: `command not found - errcode: E_CODE_CMD_NFOUND = 127`
- [x] validate command is not executable, error msg: `permission denied - errcode: E_CODE_CMD_NEXEC = 126`
- [x] validate infile/outfile is not existed, error msg: (my bash is showing 1?)`No such file or directory - errcode: E_CODE_FILE = 1

## exec
- [x] for path finding, access() needs to be seperated to check for file existance and file access seperately to get the proper error message, even the possiblity of a same executable named file can be accessible in 1 folder, and not accessible in another folder, so I guess keep track of where the files exist and then find which one, if any, is accessible / executable.
- [x] builtins properly into exec
- [x] input "$HOME here '$HOME' test"
Expected output:
bash: /Users/lumik here '/Users/lumik' test: No such file or directory
Current output:
minishell: /Users/lumik: is a directory

## builtins
- [x] export without args needs to print sorted list of vars
- [x] need to be properly handled from execution
- [x] exit, cd, export, unset need to be not forked if they are 