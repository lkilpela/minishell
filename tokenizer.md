### `echo "Hello, World!" > output.txt.`

```
[WORD("echo"), SPACE, D_QUOTE, WORD("Hello, World!"), D_QUOTE, SPACE, GREAT, SPACE, WORD("output.txt")]
```
<details>
  <summary>Click to expand </summary>

This command would be tokenized as follows:

`echo` - This is a `WORD` token. It's the name of the command to be executed.

` `(space) - This is a `SPACE` token. It separates the command from its arguments.

`"Hello, World!"` - This is a `D_QUOTE` token followed by a `WORD` token followed by another `D_QUOTE` token. The D_QUOTE tokens represent the start and end of a double-quoted string, and the `WORD`token represents the string itself.

` `(space) - This is another `SPACE` token. It separates the command and its arguments from the redirection operator.

`>` - This is a `GREAT` token. It represents the redirection operator, which redirects the output of the command to a file.

` `(space) - This is another `SPACE` token. It separates the redirection operator from the file name.

`output.txt` - This is another `WORD` token. It represents the name of the file to which the output should be redirected.
</details>

### `echo "Your home directory is $HOME"`  

> Output: Your home directory is /Users/lumik

```
[WORD("echo"), SPACE, D_QUOTE, WORD("Your home directory is "), VAR("HOME"), D_QUOTE]
```
<details>
  <summary>Click to expand </summary>

`echo`: This is a `WORD` token that represents the echo command.

` `(space): This is a `SPACE` token that represents the space character between echo and the quoted string.

`"`: This is a `D_QUOTE` token that represents the opening double quote of the quoted string.

`Your home directory is "`: This is a `WORD` token that represents the part of the quoted string before the variable.
- "Your home directory is " is a single word from the shell's perspective. When the shell executes the echo command, it passes "Your home directory is " (minus the quotes) as a single argument to the echo command.
- If tokenize "Your home directory is " into individual words -> need to handle quoted strings separately in parser, as they don't follow the usual word separation rules. This would complicate the parser and potentially lead to errors. By treating "Your home directory is " as a single WORD token, it simplify the parser and make tokenization more accurate.

`HOME`: This is a `VAR` token that represents the `HOME` variable. This token is used for variable expansion.

`"`: This is a `D_QUOTE` token that represents the closing double quote of the quoted string.
</details>