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
| 16 | `echo$USEReee` | token_value: echo$USEReee, token_type: WORD;|