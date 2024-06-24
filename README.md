<h1 align="center">
	<img src="https://github.com/lkilpela/42-project-badges/blob/main/badges/minishelle.png" />

</h1>

<p align="center">
	<b><i>As beautiful as a shell</i></b><br>
</p>

<p align="center">
    <img alt="score" src="https://img.shields.io/badge/score-101%2F100-brightgreen" />
<p align="center">
    <img alt="group" src="https://img.shields.io/badge/group-yellow" />
    <img alt="estimated time" src="https://img.shields.io/badge/estimation-210hours-blue" />
    <img alt="XP earned" src="https://img.shields.io/badge/XP-2814-orange" />
<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/lkilpela/minishell?color=lightblue" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/lkilpela/minishell?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/lkilpela/minishell?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/lkilpela/minishell?color=green" />
</p>

## 🐚 About The Project

**This project is co-written by Allar K. & Lumi K.**

The MiniShell project is a hands-on initiative aimed at creating a simple, yet functional shell, similar to a lightweight bash. This project is an excellent opportunity to delve into the intricacies of processes and file descriptors, offering a practical learning experience in system programming and command line interface development.

### Mindmap

![MindMap](doc/Mind_Maps.jpg "This is project mindmap")

## 🏁 Getting Started
### Prerequisites
- `gcc` or `clang`
- `make`

### 🛠️ Installation & Setup

1. Clone the repository: 
```
git clone https://github.com/lkilpela/minishell.git
```

2. Compile the project: `make`

### 🚀 How to Use

After compiling the project, you can start the MiniShell by running the following command in the terminal:

`./minishell`

You'll be greeted by the MiniShell prompt, where you can start typing and executing commands, exploring the functionalities of your custom shell.

## 📝 Evaluation Requirements

The MiniShell project will be evaluated based on the following criteria:

1. **Functionality**: 
   - Correct implementation of basic shell commands (e.g., `cd`, `ls`, `echo`).
   - Ability to execute external programs.
   - Proper handling of environment variables.

2. **Process Management**:
   - Correct implementation of process creation and management.
   - Implementation of job control, including foreground and background processes.

3. **File Descriptor and Redirection**:
   - Proper handling of standard input, output, and error redirections.
   - Implementation of pipelines between commands.

4. **Signal Handling**:
   - Correct handling of signals such as `SIGINT` (Ctrl+C) and `SIGQUIT` (Ctrl+\).

5. **Memory Management**:
   - Efficient memory usage and no memory leaks.

6. **Coding Style and Documentation**:
   - Code should be well-organized and readable.
   - Adequate documentation and comments explaining the logic and flow of the program.


### 🧑‍💻 Peer Evaluations (3/3)

> **Peer 1**: "Great job! Your code is well organized and you were able to provide good explanations. There was one leak from readline which is explictly mentioned in the subject as not your problem. No other leaks were found. We tried a lot of different combinations of redirections, heredocs and pipes and everything works well. Good job with env variable handling as well. Good luck on the next project."

> **Peer 2**: "This project was really well done! They both show good commands/knowledge about the program that they wrote. Also, because I am also currently working on this project, so it helped me clear with some ideas/approach with my own program as well! We went through the evaluation sheet and tested each cases according the sheet. I didn't know much of the edge cases so I was only testing based on the sheets and they handled all the tests that I did and more! good job!"

> **Peer 3**: "Very nice looking minishell. Clever way of using a function that returns a pointer to their struct and allowed handling signals without using a global variable. Tested all cases in the evaluation sheet and then some more. They also handled local variables. Valgrind only showed readline leaking. We briefly looked at the code as well. Keep up the good work!"