# To-Do List

## signals
- [ ] signal handling in child process.
- [ ] signal handling in heredoc.
- [ ] probably more signal stuff.
- [ ] manual_tests/signals.txt 

## validate
- [x] fixed a bug with multiple redirections in the same command (heredoc was getting overwritten by a normal input file, when it shouldn't be)
## parse
## exec
- [x] make in our minishell does not work, not sure why (started working because of proper envp values to execve)
- [x] updated variables to be sent to the execve


## builtins

bash-3.2$ unset PWD
bash-3.2$ echo $PWD

bash-3.2$ cd ..
bash-3.2$ echo $PWD
/Users
bash-3.2$ env | grep PWD
bash-3.2$ env | grep OLDPWD
bash-3.2$ export PWD
bash-3.2$ env | grep PWD
PWD=/Users


- [ ] some variables are considered "read-only" and cannot be unset or modified: BASH, BASH_VERSION, HOME, PATH, PWD, UID, HOSTNAME. Check if we are able to unset or modify these at school? At home, we has admin right.
example: export HOME="", unset HOME

- [x] update $OLDPWD and $PWD env variables when using 'cd'.
- [ ] update $SHLVL properly
- [ ] specical case export `export whatever=test | grep ok | cat`
- [ ] Test  40: ❌ cd $PWD hi (NEED TO CHECK THE BASH VERSION OF SCHOOL COMPUTER)
mini exit code = 1
bash exit code = 0
mini error = ( too many arguments)
bash error = ()

- [ ] bash changes the current directory 
```
minishell$ 

minishell: cd: too many arguments
```
```
bash$ pwd
/Users/lumik/workspace/git/minishell
bash$ cd .. hi
bash$ pwd
/Users/lumik/workspace/git
```
different for me
```
a@Allar:~/minishell$ pwd
/home/a/minishell
a@Allar:~/minishell$ cd .. hi
bash: cd: too many arguments
a@Allar:~/minishell$ pwd
/home/a/minishell
a@Allar:~/minishell$
```

## NORM

1. minishell.c

2. Tokenizer
token_list.c: Error!
Error: TOO_MANY_LINES       (line:  46, col:   1):      Function has more than 25 lines

3. minishell.h
Error: PREPROC_CONSTANT     (line:  37, col:  20):      Preprocessor statement must only contain constant defines
Error: PREPROC_CONSTANT     (line:  38, col:  23):      Preprocessor statement must only contain constant defines
Error: PREPROC_CONSTANT     (line:  40, col:  22):      Preprocessor statement must only contain constant defines

4. Unused function
errors.c
int	pipe_start_end(t_token_list *tokens)

# DONE

## validate
- [x] split validate_command into smaller functions
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
- [x] bash has exit code `0` vs minishell has exit code `139`
```
minishell$ $EMPTY
minishell$ echo $?
139
```
- [x] SEGFAULT
```
minishell$ echo $USER
lumik
minishell$ unset USER
minishell$ echo $USER
zsh: segmentation fault  ./minishell
```
```
minishell$ <
minishell: syntax error near unexpected token `newline'
zsh: segmentation fault  ./minishell
```

- [x] Echo's ouput is missing `-`

echo - "" "  " hello

Expected output: 
```
-     hello
```

Current output:
```
minishell$ echo - "" "  " hello
    hellominishell$ 
```

- [x] SEGFAULT
minishell$ doesntexist
minishell: doesntexist: command not found
minishell$ $EMPTY
zsh: segmentation fault  ./minishell
https://github.com/lkilpela/minishell/commit/9ca9fad2ad6d794c093847263293970c69d47c00
- [x] for path finding, access() needs to be seperated to check for file existance and file access seperately to get the proper error message, even the possiblity of a same executable named file can be accessible in 1 folder, and not accessible in another folder, so I guess keep track of where the files exist and then find which one, if any, is accessible / executable.
- [x] builtins properly into exec
- [x] input "$HOME here '$HOME' test"
Expected output:
bash: /Users/lumik here '/Users/lumik' test: No such file or directory
Current output:
minishell: /Users/lumik: is a directory

## builtins
- [x] Test  50: ❌ exit hello 
mini exit code = 2
bash exit code = 255
- [x] bash does not return an error, it treats it as a request to export an exising shell var
```
minishell$ export hello
minishell: export: : hello: not a valid identifier

bash$ export hello
bash$ echo $hello

bash$ 
```
- [x] export without args needs to print sorted list of vars
- [x] need to be properly handled from execution
- [x] exit, cd, export, unset need to be not forked if they are
- [x] exit code should be 1 & ``A-'`
```
minishell$ export A-
minishell: export: : A-: not a valid identifier
minishell$ echo $?
0
```
- [x] ~~after `unset PATH` and then `echo $PATH` should give an error message~~ I see still bash just printing newline / nothing just like ours
```
bash$ unset PATH
bash$ echo $PATH
bash: sed: No such file or directory
```


## parse
- [x] in case of mutlple infiles when one file is invalid, it should NULL the command. (probably need to move file opening to parser then)
- [x] SEGFAULT with minishell$ cat `minishell$ cat <minishell.h <<HERE <missing | ls`
**I CHECKED AND IT WORKED LIKE BASH. What case you meant need to be fixed?**
```
minishell$ echo "This is a valid file." > valid1.txt
minishell$ echo "This is another valid file." > valid2.txt
minishell$ touch invalid.txt
minishell$ chmod -r invalid.txt
minishell$ cat valid1.txt valid2.txt invalid.txt
This is a valid file.
This is another valid file.
cat: invalid.txt: Permission denied
minishell$ cat valid1.txt valid2.txt invalid12.txt | cat valid1.txt
This is a valid file.
cat: invalid12.txt: No such file or directory
minishell$ echo $?
0
```
- [x] handle `cat <minishell.h <<HERE <missing | ls`
```
minishell$ cat <minishell.h <<HERE <missing | ls
> HERE
minishell: missing: No such file or directory
```
Expected output: `bash: minishell.h: No such file or directory`

- [x] handle `cat <minishell.h <<HERE | cat`
```
minishell$ cat <minishell.h <<HERE | cat
> HERE
```
Expected output: `bash: minishell.h: No such file or directory`

- [x] handle `cat <minishell.h <<HERE <missing <<DOC | echo oi`
```
minishell$ cat <minishell.h <<HERE <missing <<DOC | echo oi
> HERE
> DOC
> oi
```
Expected output:
```
bash: minishell.h: No such file or directory
oi
```
- [x] simple_cmd and maybe parser function refactor for readability and simplicity
