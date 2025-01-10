# Simple Shell

## Description
The simple_shell project is a basic implementation of a UNIX command line interpreter. It is a minimalist shell that executes commands interactively by displaying a prompt, waiting for the user to type a command, and then executing the command. This project aims to provide a practical understanding of the internal workings of command interpreters in UNIX systems.

## Requirements 

All files have been programmed and tested in an Ubuntu 20.04 LTS environment and compiled using gcc.
the code respects the Betty style.pl and betty-doc.pl requirements.

## Features

Displays a prompt and waits for the user to type a command.

Executes commands with or without arguments.

Handles errors and displays appropriate messages if a command cannot be found or executed.

Handles the end-of-file (Ctrl+D) condition to gracefully exit the shell.

Utilizes system calls fork and execve for command execution.

## Compilation

To compile the code, use the following command:
```c
"gcc -Wall -Wextra -Werror -pedantic simple_shell.c -o hsh"
```
## Usage

Once compiled, you can run the shell using the following command:
```c
./hsh
```
Examples
```c
$ ./hsh
$ ls
file1 file2 file3
$ /bin/ls -l
-rw-r--r-- 1 user user 123 Jan 1 12:00 file1
-rw-r--r-- 1 user user 456 Jan 1 12:01 file2
-rw-r--r-- 1 user user 789 Jan 1 12:02 file3
$ echo "Hello, World!"
Hello, World!
$ /bin/echo "Hello, World!"
Hello, World!
$ ^D
```
## Interactive mode

## Non interactive mode

## Future Features

Adding advanced features such as redirection, pipes, and script handling.

Support for built-in commands and special characters.

## functions_tools

tools2.c contains utility functions that are crucial to the proper operation of the _printf function.

## valgrind and test

```c
valgrind --leak-check=full ./hsh
```

## man page



## flowchart



## Authors

VILLESSOT - Julien
DANIEL - Alexandre
