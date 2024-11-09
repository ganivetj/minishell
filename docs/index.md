# Minishell Project Documentation

## Overview

Minishell is a Unix-like shell that emulates the behavior of a command-line interpreter, accepting and executing commands while offering core shell functionalities. Designed to adhere to Unix and POSIX standards, it handles parsing, redirections, pipes, and various built-in commands, providing an educational experience in building a CLI from scratch.

Minishell uses several custom libraries—`libft`, `ft_printf`, and `get_next_line`—to manage memory, handle input/output, and provide efficient command execution. Each of these libraries is tailored to specific needs within the shell, ensuring robust and reusable solutions throughout the codebase.

---

## Core Components

### 1. `libft`
The `libft` library serves as a foundational utility library, offering alternatives to standard C library functions like `malloc`, `free`, `strdup`, `atoi`, and others. By providing a custom library (`libft.a`), Minishell gains reliable, optimized implementations for common tasks, adding consistency and control over memory management.

**Roles of `libft` in Minishell:**

- **Memory Management**: Efficient memory allocation is essential in shell environments where dynamic strings are frequently created, modified, and freed.
- **String Manipulation**: Commands like `ft_split` assist in parsing and handling arguments, crucial for command processing.
- **Error Handling**: Custom error handlers in `libft` allow Minishell to gracefully exit on critical errors without abrupt interruptions.

In Minishell, `libft` enhances readability and reliability by offering a set of tested functions that replace standard library calls, supporting everything from parsing to custom error messages.

### 2. `ft_printf`
The `ft_printf` library provides formatted output, essential for displaying shell prompts, errors, and command output in a consistent, controlled manner. This custom implementation of `printf` handles various format specifiers (`c`, `s`, `p`, `d`, `i`, `u`, `x`, `X`, `%`) and allows for flexible, well-formatted output without the dependencies of standard `printf`.

**Key roles of `ft_printf` in Minishell:**

- **Prompt and Command Output**: Ensures consistent formatting for shell prompts and error messages.
- **Dynamic Content Formatting**: Supports variable replacement, allowing formatted output that includes dynamic values like environment variables.

`ft_printf` adds flexibility and control over output, making it an efficient alternative for Minishell’s specific formatting needs.

### 3. `get_next_line`
The `get_next_line` (GNL) function handles line-by-line input from file descriptors (including standard input), essential for user interactivity in the shell. With support for buffered reading and memory efficiency, it reads each line until an end-of-line or EOF, managing memory effectively to avoid leaks.

**Roles of `get_next_line` in Minishell:**

- **Command Parsing**: Captures each line of user input, which is then parsed and tokenized.
- **Redirection Support**: Manages input from multiple sources (files and pipes) by processing each line individually.
- **Buffered Reading**: Optimizes performance for lengthy commands, scripts, or piped input.

This library simplifies input handling, abstracting away the details of buffer management and enabling line-by-line processing, which is ideal for Minishell’s command-line functionality.

---

## Key Shell Functionalities

### Parsing and Execution Flow
Minishell’s parsing system involves tokenizing input, recognizing built-in and external commands, and handling arguments and operators. This includes:

1. **Lexical Analysis**: Breaking down commands using `libft` functions (e.g., `ft_split`), managing quotes, special characters, and whitespace.
2. **Syntax Parsing**: Identifying commands, arguments, and operators like pipes (`|`) and redirections (`>`, `<`).
3. **Execution Handling**: Executing built-in commands or external programs using `execve`.

### Redirections and Pipes
Minishell implements pipes and redirections to link commands and manage I/O efficiently.

- **Redirection Management**: Sets up file descriptors to redirect input/output as needed, using `dup2` to remap them for specific commands.
- **Pipes**: Links multiple commands, passing output from one command as input to the next using file descriptors.

### Signal Handling
Minishell responds to Unix signals (`SIGINT`, `SIGQUIT`) to manage command interruption and keep the interface responsive.

- **Command Interruption**: Stops currently executing commands without crashing the shell.
- **Prompt Control**: Clears and redisplays the prompt on specific signals.

---

## Integration of Libraries in Minishell

### Consistency and Efficiency
`libft`, `ft_printf`, and `get_next_line` provide a cohesive, modular set of tools that enhance code consistency and maintainability. By integrating these custom libraries, Minishell maintains a high level of control over memory management and performance, critical for system-level applications.

### Educational Value
Developing and using `libft`, `ft_printf`, and `get_next_line` provides insight into core programming concepts like memory management, formatted output, and file I/O. Minishell emphasizes modular design and efficient coding, reinforcing essential C programming skills that scale to larger projects.

---

## Conclusion

Minishell offers an immersive experience in shell development, covering Unix-like systems, process management, and inter-process communication. The use of custom libraries (`libft`, `ft_printf`, `get_next_line`) reinforces foundational programming skills and makes Minishell an educational and functional CLI project.

