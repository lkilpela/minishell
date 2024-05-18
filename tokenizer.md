Start
  |
  v
Read character
  |
  v
Is it a quote (" or ')? ---- Yes ----> Start or stop quoted string
  |                             |
 No                             v
  |                     Read next character
  v                             |
Is it a space? ---- Yes ----> Treat as part of current token
  |                             |
 No                             v
  |                     Read next character
  v                             |
Is it a special character? ---- Yes ----> Treat as part of current token
  |                             |
 No                             v
  |                     Read next character
  v                             |
Is it a dollar sign? ---- Yes ----> Treat as start of variable
  |                             |
 No                             v
  |                     Read until non-variable character
  v                             |
Treat as part of current token  |
  |                             v
  v                     Replace with variable value
Read next character <-----------|
  |
  v
End

1. The shell reads the input one character at a time.
2. If it encounters a space, it treats everything it has read so far as a single token, unless it's currently inside a quoted string.
3. If it encounters a quote, it starts or stops a quoted string. While inside a quoted string, spaces are treated as normal characters, not as token separators.
4. If it encounters a special character like |, <, or >, it treats it as a separate token, unless it's currently inside a quoted string.
5. If it encounters a dollar sign, it treats the following characters as a variable name and replaces them with the variable's value, unless it's currently inside a single-quoted string.