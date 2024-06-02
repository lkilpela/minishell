# To-Do List

## exec
- [ ] for path finding, access() needs to be seperated to check for file existance and file access seperately to get the proper error message, even the possiblity of a same executable named file can be accessible in 1 folder, and not accessible in another folder, so I guess keep track of where the files exist and then find which one, if any, is accessible / executable.
- [ ] hangs when inaccessible file given to redirections <br>
When ```chmod 000 infile```<br>
```>infile cat | cat | <Makefile cat | grep CC``` <br>
does the last part correctly ```<Makefile cat | grep CC```,<br>
but hangs cause of inaccessible file ```>infile``` <br>
can unhang if you open second terminal and do `pkill cat`
just single command `<infile cat` works and prints permission denied
- [ ] make does not work, not sure why
- [ ] temp


## builtins
- [ ] exit isnt exiting.
- [ ] exit, cd, export, unset need to be not forked, to handle everythign properly