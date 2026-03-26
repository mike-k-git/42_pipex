_This project has been created as part of the 42 curriculum by mkugan._

# Pipex

A Unix pipeline recreation in C, inspired by shell behavior.

This project replicates how commands are chained using pipes (|) in a shell, handling process creation, file descriptors, and execution flow.

## Features

### Mandatory

Execute two commands with a pipe:

```bash
 < infile cmd1 | cmd2 > outfile
```

Handles:
- input/output redirection
- environment PATH resolution
- process forking & piping
- error handling

### Bonus

Multiple pipes:

```bash
< infile cmd1 | cmd2 | cmd3 | ... | cmdN > outfile
```

Here-doc support:

```bash
./pipex here_doc LIMITER cmd cmd1 outfile
```

## Build

### Clone the repository

```bash
git clone https://github.com/mike-k-git/42_pipex.git
cd 42_pipex
```

### Initialize submodules

```bash
git submodule update --init --recursive
```

This project uses submodules for dependencies:
- 42_libft
- 42_ft_printf
- 42_get_next_line

### Compile

```bash
make
make bonus
```
