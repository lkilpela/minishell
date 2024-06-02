# To-Do List

## exec
- [ ] for path finding, access() needs to be seperated to check for file existance and file access seperately to get the proper error message, even the possiblity of a same executable named file can be accessible in 1 folder, and not accessible in another folder, so I guess keep track of where the files exist and then find which one, if any, is accessible / executable.
- [ ] errors and problems whenever a command before in a pipeline doesnt have any output, getting bad file descriptor errors, (I think its when its trying to duplicate a file thats closed) also child processes hang whenever inaccessible file (chmod 000) is gives as input in a pipeline situation
`<blocked cat` works fine `<blocked cat | cat` hangs etc these 2 might be the same problem
- [ ] temp
- [ ] temp


## builtins
- [ ] exit isnt exiting.
- [ ] exit, cd, export, unset need to be not forked, to handle everythign properly