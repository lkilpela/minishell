| Test Case Number | Input | Expected Output |
| --- | --- | --- |
| 1 | `ls` | token_value: ls, token_type: WORD |
| 2 | `ls -l` | token_value: ls, token_type: WORD; token_value: -l, token_type: WORD |
| 3 | `ls -l -a` | token_value: ls, token_type: WORD; token_value: -l, token_type: WORD; token_value: -a, token_type: WORD |
| 4 | `ls -l \| grep .txt` | token_value: ls, token_type: WORD; token_value: -l, token_type: WORD; token_value: \|, token_type: PIPE; token_value: grep, token_type: WORD; token_value: .txt, token_type: WORD |
| 5 | `ls -l > output.txt` | token_value: ls, token_type: WORD; token_value: -l, token_type: WORD; token_value: >, token_type: REDIRECTION; token_value: output.txt, token_type: WORD |
| 6 | `echo "Hello World"` | token_value: echo, token_type: WORD; token_value: Hello World, token_type: WORD |
| 7 | `echo $HOME` | token_value: echo, token_type: WORD; token_value: $HOME, token_type: SPECIAL_CHAR |
| 8 | `ls -l; echo "Hello World"` | token_value: ls, token_type: WORD; token_value: -l, token_type: WORD; token_value: ;, token_type: SEMICOLON; token_value: echo, token_type: WORD; token_value: Hello World, token_type: WORD |
| 9 | `echo $PATH` | token_value: echo, token_type: WORD; token_value: $PATH, token_type: SPECIAL_CHAR |
| 10 | `echo `date`` | token_value: echo, token_type: WORD; token_value: date, token_type: BACKTICK |


