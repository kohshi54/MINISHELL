# MINISHELL

## Overview
MINISHELL is a minimal implementation of a bash-like shell. It is designed to interpret and execute commands as a standard Unix shell would, with a focus on handling command-line operations through external commands rather than built-in features.

## Features
- **Prompt Display:** The shell displays a prompt when it is ready to accept a new command.
- **Command History:** Maintains a history of commands that have been entered for easy recall.
- **Executable Search:** Searches for and launches executables based on the PATH environment variable or via relative/absolute paths.

## How It Works
MINISHELL operates through a series of steps to process and execute commands:

1. **Input**: The shell reads the input provided by the user on the command line.
2. **Lexing**: A lexer tokenizes the input, breaking it down into recognized tokens which include commands, arguments, and operators for redirection and piping.
3. **Parsing**: A parser performs recursive descent parsing to analyze the structure of the command. During this phase, it constructs a syntax tree that represents the hierarchical structure of the input.
4. **Conversion**: A converter transforms the syntax tree into a format that can be executed. This step involves resolving command names to system paths and preparing the data for execution.
5. **Execution**: An executor runs the command sequence, handling any required file redirections or pipelining between commands as dictated by the syntax tree.

By breaking down command execution into these steps, MINISHELL ensures that each part of the user's input is accurately interpreted and carried out according to shell operation principles.


## Quoting Mechanism
- **Single Quotes (')**: Treats the enclosed sequence of characters as a single string, preventing the interpretation of meta-characters.
- **Double Quotes (")**: Similar to single quotes, but allows the interpretation of the dollar sign (`$`) to recognize variables.

## Redirections
- **Input Redirection (<)**: Redirects input from a file to a command.
- **Output Redirection (>)**: Redirects output from a command to a file, overwriting the existing contents.
- **Here Document (<<)**: Reads input until a line containing the specified delimiter is identified. This input method does not affect the command history.
- **Append Output Redirection (>>)**: Redirects output from a command to a file, appending it to the existing contents rather than overwriting.

## Pipes
- Implements the pipe (`|`) character to allow the output of one command to serve as the input to the next command in sequence.

## Usage
The shell can be invoked from the terminal. Once started, it operates by reading user commands and executing the corresponding programs accordingly.

## Limitations
- The shell does not implement built-in commands and relies entirely on external commands for functionality.

## Installation and Running
To install MINISHELL, follow these steps:

1. Clone the repository to your local machine.
2. Navigate to the cloned directory.
3. Run `make` to compile the shell.

To start MINISHELL, run the following command in the terminal after compilation:

```bash
./minishell
