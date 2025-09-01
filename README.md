# Minishell

A small, POSIX-like shell written in C. Minishell implements a subset of Bash behavior, including a prompt, command execution with pipelines and redirections, environment variable management, heredocs, and common built-in commands.

This project is a great exercise in process management, parsing, error handling, memory management, and terminal signal handling.

## Table of contents
- What is “handling” in Minishell?
- Features
- Quick start
- Usage
- Project layout
- How it works (high-level design)
- Signals and terminal behavior
- Error handling and exit codes
- Memory management
- Known limitations
- Development notes
- License

---

## What is “handling” in Minishell?

When we say “handling,” we mean how the shell accepts, interprets, transforms, and executes user input reliably. In practice, it covers:

- Input handling: reading a full line from the terminal and managing history.
- Token handling: splitting the line into tokens while respecting quotes and escapes.
- Expansion handling: replacing $VAR and $? with their values, and splitting results only when appropriate.
- Quote handling: removing quotes after they have served their syntactic role.
- Redirection handling: opening files and wiring stdin/stdout/stderr according to <, >, >>, and << (heredoc).
- Pipeline handling: connecting the stdout of one command to the stdin of the next with |.
- Builtins handling: executing shell builtins in the correct context (sometimes in the parent process).
- Signal handling: reacting properly to Ctrl-C, Ctrl-D, and Ctrl-\ while preserving a normal terminal state.
- Error handling: detecting and reporting syntax and runtime errors with correct exit statuses.
- Resource handling: tracking and freeing all allocated resources to avoid leaks.

Minishell brings all of these “handling” responsibilities together so commands behave closely to what users expect from a real shell.

---

## Features

- Prompt with command history (via GNU Readline)
- Parsing with support for:
  - Single and double quotes
  - Environment variable expansion ($VAR) and last status ($?)
  - Syntax checks and error messages
- Execution engine supporting:
  - External programs looked up via PATH
  - Pipelines: cmd1 | cmd2 | ...
  - Redirections: > >> < and heredocs <<
- Built-in commands:
  - echo, cd, pwd, env, export, unset, exit
- Signal-aware interactive mode:
  - Ctrl-C interrupts the current input/command
  - Ctrl-D exits the shell when the line is empty
- Clean resource management to prevent memory leaks

---

## Quick start

Prerequisites:
- A C compiler (gcc or clang)
- make
- GNU Readline development headers and library

Install Readline:
- Debian/Ubuntu: sudo apt-get update && sudo apt-get install -y libreadline-dev
- Fedora: sudo dnf install readline-devel
- Arch: sudo pacman -S readline

Build:
- make
- make clean / make fclean / make re

Run:
- ./minishell

Note:
- The Makefile links with -lreadline and includes headers from -I/usr/include/readline.
- On macOS with Homebrew, you may need to adjust INCLUDES/LDFLAGS or export:
  - CPPFLAGS="-I$(brew --prefix readline)/include"
  - LDFLAGS="-L$(brew --prefix readline)/lib"

---

## Usage

- Run ./minishell to enter the interactive shell.
- Type commands as in a typical shell:
  - External: ls -la
  - Pipelines: ls -la | grep 'd'
  - Redirections: grep main < src/file.c > out.txt
  - Append redirection: echo hello >> out.txt
  - Heredoc:
    cat << EOF
    line 1
    line 2
    EOF
  - Variables:
    export NAME=world
    echo "hello $NAME"
  - Last exit status:
    echo $?
- Builtins:
  - echo [args...]
  - cd [dir]
  - pwd
  - env
  - export KEY=VALUE or export KEY
  - unset KEY
  - exit [status]

Exit:
- Ctrl-D on an empty prompt or the exit builtin.

---

## Project layout

Top-level:
- Makefile
- minishell.c — entry point and main loop
- includes/ — public headers for the modules (exec.h, parse.h, minishell.h)

Source modules (as referenced by the Makefile):
- builtins/
  - my_cd.c, my_echo.c, my_env.c, my_exit.c, my_export.c, my_pwd.c, my_unset.c
  - my_utils*.c — helper routines for builtins
- exec/
  - exec.c — orchestrates command and pipeline execution
  - exec_utils*.c — process and pipe setup helpers
  - redirect_utils.c — applies <, >, >>, and file descriptor wiring
- helper_utils/
  - ft_split.c — string splitting utilities
  - gc.c — simple allocation tracker to free resources in one place
  - utils*.c — general utilities used across modules
  - copy_env.c — copies and manages the environment
- herdoc/ (heredoc)
  - heredoc.c, heredoc_utils*.c — implements << delimiter reading and temporary storage
- parse/
  - tokeniziation/*.c — tokenization logic (splitting the input into tokens)
  - parsing*.c — builds command structures from tokens and checks syntax
  - creat_command.c — assembles parsed command nodes/segments
  - syntax_errors.c — reports parsing errors
  - expansions/*.c — $VAR and $? expansion and post-expand splitting
  - remove_quotes/*.c — strips syntactic quotes after parsing
- signal/
  - signal.c — installs and manages interactive signal handlers

Note: Some directory names intentionally mirror the sources and may contain minor typos (e.g., tokeniziation, herdoc) as reflected in the Makefile.

---

## How it works (high-level design)

1. Readline loop
   - Display prompt, read a line, add to history.

2. Tokenization
   - Split into tokens while respecting quotes and escapes. This ensures spaces inside quotes are not treated as separators.

3. Parsing and syntax validation
   - Build a structured representation of the command line (a list or pipeline of commands).
   - Validate syntax for operators like |, <, >, >>, <<.

4. Expansion
   - Replace $VAR and $? with their values.
   - Split expanded values only when appropriate (e.g., unquoted expansions).

5. Quote removal
   - Remove quotes after their structural role is complete so execution sees clean arguments.

6. Execution
   - Builtins that affect the shell state (cd, export, unset, exit) run in the parent process when required.
   - External commands are executed via fork/exec with proper PATH lookup.
   - Pipelines use pipe() to connect processes.
   - Redirections alter file descriptors before executing a command.
   - Heredocs collect input until the delimiter and feed it as stdin.

7. Cleanup
   - Close descriptors, free command structures, and clear tracked allocations before the next prompt.

---

## Signals and terminal behavior

- Ctrl-C (SIGINT)
  - At the prompt: clears the current line, prints a new prompt, exit status set to 130.
  - During a running command: interrupts the foreground process.
- Ctrl-\ (SIGQUIT)
  - Generally ignored at the prompt but forwarded to child processes.
- Ctrl-D (EOF)
  - At an empty prompt: exits the shell gracefully.

Minishell sets appropriate handlers so the terminal remains usable and stateful across prompts.

---

## Error handling and exit codes

- Syntax errors
  - Detected during parsing (e.g., unexpected token | or unmatched heredoc delimiter).
  - Printed with a clear error message; the line is not executed.

- Runtime errors
  - Command not found, permission denied, file not found for redirection, etc.
  - Exit statuses follow common Bash conventions when possible:
    - 127: command not found
    - 126: found but not executable
    - 1: general errors
    - 130: interrupted by SIGINT

- The special variable $?
  - Expands to the exit code of the last executed pipeline.

---

## Memory management

To avoid leaks and simplify teardown between prompts, Minishell centralizes allocations:
- Most dynamic allocations are registered via a lightweight allocation tracker (helper_utils/gc.c).
- On each loop iteration (or when exiting), the tracker frees owned resources in one pass.

This approach helps keep the interactive loop robust even when commands fail partway.

---

## Known limitations

Minishell intentionally implements a subset of Bash:
- No job control (e.g., fg/bg, process groups)
- No subshells with parentheses (...)
- No command substitution $(...)
- No globbing/pattern expansion (*) unless provided by the called program
- No advanced redirections like descriptor duplication (2>&1) unless implemented in redirect_utils.c
- No conditionals (&&, ||) or scripting features
- Locale and multi-byte edge cases may not be fully covered

---

## Development notes

- Build with: make
- Clean objects: make clean
- Clean all: make fclean
- Rebuild: make re
- Compiler flags: -Wall -Wextra -Werror (can be adjusted in the Makefile)
- Linked libraries: -lreadline

Directory headers live in includes/ (exec.h, parse.h, minishell.h) and are required for compilation. If you move files or rename directories, update the Makefile accordingly.

---

## License

No license file is provided. All rights reserved by the repository owner unless a license is added.

---

## Credits

- Authors: <a href="https://github.com/moraouid">moraouid</a>  &&  <a href="https://github.com/maskface02">0xm45kf4c3</a>
- Inspired by the 42 “Minishell” project specification
