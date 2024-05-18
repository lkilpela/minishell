| Test Case Number | Input | Expected Output |
| --- | --- | --- |
| 1 | `ls` | token_value: ls, token_type: WORD |
| 2 | `ls -l` | token_value: ls, token_type: WORD; token_value: -l, token_type: WORD |
| 3 | `ls -l -a` | token_value: ls, token_type: WORD; token_value: -l, token_type: WORD; token_value: -a, token_type: WORD |
| 4 | `ls -l \| grep .txt` | token_value: ls, token_type: WORD; token_value: -l, token_type: WORD; token_value: \|, token_type: PIPE; token_value: grep, token_type: WORD; token_value: .txt, token_type: WORD |
| 5 | `ls -l > output.txt` | token_value: ls, token_type: WORD; token_value: -l, token_type: WORD; token_value: >, token_type: REDIRECTION; token_value: output.txt, token_type: WORD |
| 6 | `echo "Hello World"` | token_value: echo, token_type: WORD; token_value: Hello World, token_type: WORD |
| 7 | `echo $HOME` | token_value: echo, token_type: WORD; token_value: $HOME, token_type: VAR |
| 8 | `ls -l; echo "Hello World"` | token_value: ls, token_type: WORD; token_value: -l;, token_type: WORD; token_value: echo, token_type: WORD; token_value: Hello World, token_type: WORD |
| 9 | `echo $PATH` | token_value: echo, token_type: WORD; token_value: $PATH, token_type: VAR|
| 10 | `echo 'Hello World'`	| token_value: echo, token_type: WORD; token_value: 'Hello World', token_type: WORD | 
| 11 | `username="John Doe"` | token_value: username="John Doe", token_type: WORD |
| 12 | `count=10` | token_value: count=10, token_type: WORD |
| 13 | `PATH=$HOME/bin:$PATH` | token_value: ???, token_type: ??? |
| 14 | `echo $username` | token_value: echo, token_type: WORD; token_value: John Doe (or whatever the expanded value of $username is), token_type: WORD|
| 15 | `echo $count` | token_value: echo, token_type: WORD; token_value: 10 (or whatever the expanded value of $count is), token_type: NUMBER |
| 16 | `new_var=$username` | token_value: ???, token_type: ???;|
| 17 | `echo$USEReee` | expanded_token: echolumikeee; token_value: echo, token_type: WORD; token_value: lumikeee, token_type: WORD;|
| 18 | `ARG=$USER` | expanded_var: ARG=lumik; var_name: ARG, var_value: lumik;|
| 19 | `echo $USER` | token_value: echo, token_type: WORD; token_value: lumik, token_type: WORD;|

## DOUBLE QUOTE

| Test Case Number | Input | Expected Output |
| --- | --- | --- |
| 1 | `\"echo\"` | token_value: echo, token_type: WORD;|
| 2 | `\"echo 'hello'\"` | token_value: echo 'hello', token_type: WORD;| -> RETOKENIZE
| 3 | `\"echo "hello"\"` | token_value: echo "hello" . , token_type: WORD;|
