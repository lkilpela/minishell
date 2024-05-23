| # | Input | Token_value | Token_type |
| --- | --- | --- | --- |
| 1 | `ls` | ls | WORD |
| 2 | `ls -l` | ls<br>-l | WORD<br>WORD |
| 3 | `ls -l -a` | ls<br>-l<br>-a | WORD<br>WORD<br>WORD |
| 4 | `ls -l \| grep .txt` | ls<br>-l<br>\|<br>grep<br>.txt | WORD<br>WORD<br>OP_PIPE<br>WORD<br>WORD |
| 5 | `ls -l > output.txt` | ls<br>-l<br>\><br>output.txt | WORD<br>WORD<br>OP_GREAT<br>WORD |
| 6 | `echo "Hello World"` | echo<br>Hello<br>World | WORD<br>WORD<br>WORD |
| 7 | `echo $HOME` | echo<br>/Users/lumik<br>($HOME get expanded from local var) | WORD<br>VAR |
| 8 | `ls -l; echo "Hello World"` | ls<br>-l;<br>echo<br>Hello<br>World | WORD<br>WORD<br>WORD<br>WORD<br>WORD |
| 9 | `echo $PATH` | echo<br>/usr/local/bin:...<br>($PATH get expanded from local var) | WORD<br>VAR|
| 10 | `echo 'Hello World'`	| echo<br>Hello<br>World | WORD<br>WORD<br>WORD | 
| 11 | `username="John Doe"` | username=John Doe | WORD |
|    | `echo $username` | echo<br>John Doe | WORD<br>WORD |
|    | `new_var=$username` | new_var=John Doe | WORD |
|    | `echo $new_var` | echo<br>John Doe | WORD<br>VAR |
| 12 | `count=10` | count=10 | WORD |
|    | `echo $count` | echo<br>10 | WORD<br>WORD |
| 13 | `PATH=$HOME/bin:$PATH` | ? | ? |
| 14 | `echo$USEReee` | echolumikeee | WORD |
| 15 | `ARG=$USER` | ARG=lumik | WORD |
|    | `echo $USER` | echo<br>lumik | WORD<br>WORD |

## QUOTE

| # | Input | Token_value | Token_type |
| --- | --- | --- | --- |
| 1 | `"echo"` | echo | WORD|
| 2 | `"echo 'hello'"` | echo<br>hello | WORD<br>WORD |
| 3 | `"echo "hello""` | echo<br>hello | WORD<br>WORD |
| 4 | `echo '$USER'` | echo<br>$USER | WORD<br>WORD |
| 5 | `"$HOME here '$HOME' test"` | /Users/lumik here '/Users lumik' test | WORD |
| 6 | `"'$HOME' here $HOME test"` | '/Users/lumik' here /Users/lumik test | WORD |
| 7 | `echo "test '$HOME' whatever"` | echo<br>test '/Users/lumik' whatever | WORD<br>WORD |
| 8 | `"hello"'$HOME'` | hello$HOME | WORD |
| 9 | `"hello"$HOME"test""test2"` | hello/Users/lumiktesttest2 | WORD |

