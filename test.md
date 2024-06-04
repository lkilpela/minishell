# TOKENIZER

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
| 14 | `echo$USEReee` | echo<br>emptystring | WORD |
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

test'okayy' "TEST'inner'Test $HOME" | test <what <<okay
```
a_token_value: test'okayy'          a_token_type: WORD
a_token_value: "TEST'inner'Test /Users/lumik" a_token_type: WORD
a_token_value: |                    a_token_type: OP_PIPE
a_token_value: test                 a_token_type: WORD
a_token_value: <                    a_token_type: OP_LESS
a_token_value: what                 a_token_type: WORD
a_token_value: <<                   a_token_type: OP_DLESS
a_token_value: okay                 a_token_type: WORD
```

test'okayy' "TEST'inner'Test $HOME" "|" "test" <what <<okay
```
a_token_value: test'okayy'          a_token_type: WORD
a_token_value: "TEST'inner'Test /Users/lumik" a_token_type: WORD
a_token_value: "|"                  a_token_type: WORD
a_token_value: "test"               a_token_type: WORD
a_token_value: <                    a_token_type: OP_LESS
a_token_value: what                 a_token_type: WORD
a_token_value: <<                   a_token_type: OP_DLESS
a_token_value: okay                 a_token_type: WORD
```

test $HOME"ANDME is $USER '$HOME'again" 'someting $HOME not expanded'
```
a_token_value: test                 a_token_type: WORD
a_token_value: /Users/lumik"ANDME is lumik '/Users/lumik'again" a_token_type: WORD
a_token_value: 'someting $HOME not expanded' a_token_type: WORD
```

# HEREDOC

1. Single line
```c
minishell$ <<END
> This is a test.
> END
This is a test.
```

2. Multiple lines of input

```c
minishell$ bash-3.2$ cat <<EMD
> hello
> $USER
> EMD
hello
lumik
heredoc> Line 1.
heredoc> Line 2.
heredoc> Line 3.
heredoc> STOP
Line 1.
Line 2.
Line 3.
```

3. Variable expansion

```c
minishell$ <<END
> test
> $USER
> END
test
lumik
```

```c
minishell$ <<END
> Hello, $USER.
> END
Hello, lumik.
```

4. No delimeter

## ERROR
```c
minishell$ <<
minishell: syntax error near unexpected token `newline'
```

5. delim is VAR

```c
minishell$ <<$TEST
>hello
>$TEST
```

```c
minishell$ <<$USER
>hello
>$USER
```

## PARSER

cat <<END | grep "hello" | wc -l > output

cat <END | grep "hello" | wc -l > output

## PIPE

echo "Hello, World!" | cat

ls -l | grep ".txt" | wc -l

< infile grep hello | wc -l < output

cat <<EOF | wc -l
Hello, World!
EOF
Expected output: 1

cat <<EOF | wc -l
Hello,
World!
EOF
Expected output: 2

cat <<EOF | grep "World" | wc -l
Hello,
World!
EOF
Expected output: 1

cat <<EOF | wc -l > output.txt
Hello, World!
EOF
Expected output: No output on the terminal, but the file output.txt should contain 1.

## APPEND

1. Basic:
```
echo "hello" > output
echo "world" >> output
cat output.txt
```
Expected output:
```
hello
world
```

2. Multiple lines:
```
echo "hello" > output
echo "world" >> output
echo "!" >> output
cat output
```
Expected output:
```
hello
world
!
```

3. Append with pipe:
```
echo "hello" | cat > output
echo "world" | cat >> output
cat output
```
Expected output:
```
hello
world
```

4. Append with heredoc:
```
cat <<EOF > output
Hello,
EOF
cat <<EOF >> output
World!
EOF
cat output
```
Expected output:
```
Hello,
World!
```

## VALIDATION

### Command not found:

< in xxx | wc > out 
```
minishell: xxx: command not found
```
< in wc | xxx > out
```
minishell: xxx: command not found
```
< in xxx | /xxx/xxx > out
```
bash: xxx: command not found
bash: /xxx/xxx: No such file or directory
```
