# Minishell - Unix Shell Implementation

## Overview
This project is a simplified Unix shell implemented in C. It allows users to execute programs through a menu-driven interface and demonstrates core
operating system concepts such as process creation, piping, and input/output redirection using POSIX system calls.

## Features
- Execute external programs using `fork`, `execvp`, and `wait`
- Pipe output from one program into another
- Redirect program output to a file
- Menu-driven command selection

## Programs Included
- `newshell.c` – Main shell program
- `letters.c` – Prints lowercase letters a–z
- `numbers.c` – Prints numbers 0–9
- `firstname.c` – Prints a provided name argument
- `userinput.c` – Reads input and converts it to uppercase

## Tech Stack
- C
- POSIX system calls
- Unix/Linux environment

## How to Build and Run
```bash
make
./newshell
```

## What I Learned
- Process creation and management using `fork` and `wait`
- Executing external programs with `execvp`
- Inter-process communication using pipes
- Input/output redirection with Unix file descriptors
