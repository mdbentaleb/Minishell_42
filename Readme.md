# 🐚 Minishell

![Image](https://github.com/user-attachments/assets/0be2e325-1680-4c9e-b6e8-922bfb9430cd)

## 📌 Overview


**Minishell** is a core project from the 42 curriculum that replicates the behavior of a simplified Unix shell. It aims to deepen your understanding of process management, file descriptors, signals, parsing, and job control by building your own command-line interpreter from scratch in C.

## ✨ Features

* 🧠 Custom shell parsing and syntax handling
* 📜 Support for sequential and piped command execution
* 🪄 Built-in commands: `cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`, `history`
* 🌍 Environment variable management and expansion (`$VAR` support)
* 🧱 Redirections: input `<`, output `>`, append `>>`, and heredocs `<<`
* 🔗 Full support for pipelines using `|`
* 🧼 Proper memory and file descriptor management
* 📶 Signal handling: handles `EOF` (`ctl+D`), `SIGINT` (`Ctrl+C`) and `SIGQUIT` (`Ctrl+\`) gracefully
* 🧵 Forking and process execution with correct exit codes
* 🧪 Error handling for syntax errors and "command not found"
* 🔄 Command history persistence across sessions
* 🧠 Advanced quoting, escaping, and syntax error detection
* 🪄 Auto-completion support (via readline hooks)
* 📜 Custom shell prompt

## 🧭 What Minishell Supports

### 🧵 Execution Engine

* Parse and execute commands using `fork()` and `execve()`
* Wait for child processes using `wait()` / `waitpid()` and return correct exit statuses
* Execute piped commands by managing file descriptors correctly

### 🧹 Parsing & Tokenization

* Split and analyze user input: detect pipes, redirections, quotes, and variable expansions
* Respect shell grammar: handle nested quotes (`'`, `"`) and escape characters
* Handle empty inputs and multiple spaces or tabs gracefully

### ⚖️ Built-in Commands (No `execve`)

* `echo [-n]` — Print arguments
* `cd [dir]` — Change current directory
* `pwd` — Print working directory
* `export VAR=val` — Set environment variable
* `unset VAR` — Remove variable
* `env` — List environment variables
* `history` — Show command history for the current session
* `exit [code]` — Exit the shell with an optional status code

### 📂 Redirections

* `>`  — Redirect output (overwrite)
* `>>` — Redirect output (append)
* `<`  — Redirect input
* `<<` — Heredoc input until limiter is found

### 💬 Environment Variables

* Handle `$VAR` expansion from the current environment and local variables
* Expand variables inside double quotes `"`, but not inside single quotes `'`

### ⚠️ Signal Handling

* `Ctrl+C` (`SIGINT`) — Interrupts current input line without exiting
* `Ctrl+\` (`SIGQUIT`) — Ignored in the main shell, passed to child processes like in Bash
* `Ctrl+D` (`EOF`) — Exits the shell if the input line is empty (end-of-file condition)

## 🛠️ Technical Constraints

* ❌ No use of `system()`, `printf()`, or external parsing libraries
* ✅ Must use `readline` for line input and command history
* 📁 No memory or file descriptor leaks (must pass `valgrind` or `leaks`)
* 🔀 Code must comply with 42 **Norminette**:

  * Maximum 25 lines per function
  * Maximum 4 variables per function
  * Maximum 4 arguments per function

## ▶️ How to Use

### 🛠️ Compilation

To compile the project, simply run:

```bash
make
```

This will generate the `minishell` executable.

### 🚀 Running Minishell

Start your shell with:

```bash
./minishell
```

You'll be greeted with a custom prompt where you can type commands just like in Bash.

### 💡 Tips

* Use up/down arrows to navigate command history
* Chain commands using pipes (`|`)
* Redirect output and input using `>`, `>>`, `<`, and `<<`
* Use `Ctrl+C` to cancel a running foreground command
* Type `exit` to quit the shell

## 🧪 Example Usage

```shell
zmbash-2.5$ echo hello | cat -e
hellozmbash-2.5$

zmbash-2.5$ export NAME=world
zmbash-2.5$ echo $NAME
world
zmbash-2.5$

zmbash-2.5$ ls > out.txt
zmbash-2.5$ cat < out.txt | grep .c
main.c
utils.c
zmbash-2.5$
```
