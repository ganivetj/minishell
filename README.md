# Minishell

> A simple shell built from scratch to explore how command-line interfaces operate, inspired by Bash.

## Overview

Minishell is a project designed to help students explore the inner workings of a shell:

- Introduces core aspects of system programming, including process management, file descriptors, and user input handling.
- Provides hands-on experience with building a fundamental tool for interacting with Unix-like systems.

## Features

- **Prompt Display**: Shows a prompt to indicate readiness for a new command.
- **Command Execution**: Searches for executables in the system's `PATH` and executes commands using either relative or absolute paths.
- **Environment Variable Support**: Expands `$VARIABLES` and manages `$?` to store the exit status of the last executed command.
- **Signal Handling**: Implements custom behavior for `ctrl-C`, `ctrl-D`, and `ctrl-\`.
- **Input/Output Redirection**:
  - `<`: Redirects standard input.
  - `>`: Redirects standard output.
  - `<<`: Accepts input until a specified delimiter.
  - `>>`: Appends standard output.
- **Pipes**: Connects the output of one command to the input of the next using `|`.
- **Builtin Commands**:
  - `echo` (with `-n` option)
  - `cd` (changes directory)
  - `pwd` (prints current directory)
  - `export` (manages environment variables)
  - `unset` (removes environment variables)
  - `env` (lists environment variables)
  - `exit` (exits the shell)