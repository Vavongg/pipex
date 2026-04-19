<div align="center">

# 🔧 pipex

_Recreating shell pipes from scratch — `cmd1 < infile | cmd2 > outfile`, but it's your code._

[![42 School](https://img.shields.io/badge/42-School-000000?style=for-the-badge&logo=42&logoColor=white)](https://42.fr/)
[![Grade](https://img.shields.io/badge/Grade-100%2F100-success?style=for-the-badge)]()
[![Language](https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c&logoColor=white)]()
[![Norminette](https://img.shields.io/badge/Norminette-Passing-brightgreen?style=for-the-badge)]()

</div>

---

## 📖 About

**pipex** is the second UNIX project of the 42 cursus. It asks a deceptively simple question: *how does a shell pipe actually work?*

This program reproduces the behavior of:

```bash
< infile cmd1 | cmd2 > outfile
```

Using nothing but the POSIX primitives: `pipe()`, `fork()`, `dup2()`, `execve()`, `wait()`. The first real dive into **inter-process communication**, file descriptor plumbing, and `PATH` resolution.

---

## 🎯 Project scope

- ✅ **Mandatory** — two commands chained with a single pipe, infile → outfile
- ⬜ **Bonus** — `here_doc` + multiple pipes (not implemented)

---

## 🧠 How it works

The program forks into two processes connected by a pipe. One child reads from `infile`, runs `cmd1`, and writes into the pipe. The parent reads from the pipe, runs `cmd2`, and writes to `outfile`.

```
   ┌─────────────┐                                        ┌─────────────┐
   │   infile    │                                        │   outfile   │
   └──────┬──────┘                                        └──────▲──────┘
          │                                                      │
          │ STDIN                                         STDOUT │
          │                                                      │
   ┌──────▼──────┐          ┌──────────┐          ┌──────▲──────┐
   │   CHILD     │          │          │          │   PARENT    │
   │             │──────────►   PIPE   ──────────►│             │
   │   cmd1      │ STDOUT   │  fd[0]   │  STDIN   │   cmd2      │
   │             │  fd[1]   │  fd[1]   │  fd[0]   │             │
   └─────────────┘          └──────────┘          └─────────────┘
      execve(cmd1)                                    execve(cmd2)
```

### Step by step

```
1. pipe(fd)                    → create two connected file descriptors
2. fork()                      → split into child + parent
3. CHILD:
     ├─ open(infile, RDONLY)
     ├─ dup2(infile, STDIN)    → stdin now reads from infile
     ├─ dup2(fd[1], STDOUT)    → stdout now writes into the pipe
     ├─ close unused fds
     └─ execve(cmd1)           → becomes cmd1, with the right plumbing
4. PARENT:
     ├─ open(outfile, WRONLY|CREAT|TRUNC)
     ├─ dup2(fd[0], STDIN)     → stdin now reads from the pipe
     ├─ dup2(outfile, STDOUT)  → stdout now writes to outfile
     ├─ close unused fds
     └─ execve(cmd2)           → becomes cmd2
```

---

## 🔍 PATH resolution

Commands are resolved the same way a real shell does it:

```
1. Read the PATH variable from envp      (e.g., "/usr/bin:/bin:/usr/local/bin")
2. Split on ':'                          → array of candidate directories
3. For each directory:
      → join dir + "/" + command
      → access(path, F_OK) ?
      → if yes: use this path
4. Nothing found → "command not found" → exit(127)
```

This mirrors the actual `$PATH` lookup done by bash/zsh when you type a command without an absolute path.

---

## 🛠️ Build

```bash
# Clone
git clone https://github.com/Vavongg/pipex.git
cd pipex

# Build (also compiles ft_printf automatically)
make

# Cleanup
make clean    # remove .o files
make fclean   # remove .o files + binary
make re       # full rebuild
```

---

## 🚀 Usage

```
./pipex <infile> "<cmd1>" "<cmd2>" <outfile>
```

### Examples

```bash
# Equivalent to:  < infile grep "hello" | wc -l > outfile
./pipex infile "grep hello" "wc -l" outfile

# Equivalent to:  < /etc/passwd cut -d: -f1 | sort > users.txt
./pipex /etc/passwd "cut -d: -f1" "sort" users.txt

# Equivalent to:  < poem.txt tr '[:lower:]' '[:upper:]' | rev > shouted_reversed.txt
./pipex poem.txt "tr '[:lower:]' '[:upper:]'" "rev" shouted_reversed.txt
```

### Comparing with the real shell

```bash
# With pipex
./pipex infile "grep hello" "wc -l" outfile && cat outfile

# With bash
< infile grep hello | wc -l > outfile_bash && cat outfile_bash

# The outputs should be identical ✨
```

---

## ⚠️ Error handling

| Situation                       | Behavior                                  |
|:--------------------------------|:------------------------------------------|
| Wrong number of arguments (≠ 5) | `perror("bad arguments")` → exit          |
| `infile` can't be opened        | `perror(infile)` → exit                   |
| `outfile` can't be created      | `perror(outfile)` → exit                  |
| Command not found in `PATH`     | `perror("command not found")` → exit 127  |
| `execve` fails                  | `perror("command not found")` → exit 126  |

---

## 📁 Structure

```
pipex/
├── Makefile
├── include/
│   └── pipex.h
├── src/
│   ├── main.c             # pipe + fork dispatcher
│   ├── commands.c         # child() / parent() / exec_cmd()
│   ├── paths.c            # PATH parsing & executable lookup
│   └── libft/             # ft_split, ft_strjoin, ft_strdup, ft_strnstr
└── ft_printf/             # Embedded static library
```

---

## 🧪 Key concepts learned

- **`pipe()` + `fork()`** — the fundamental UNIX IPC pattern
- **File descriptor redirection** — `dup2()` and closing unused fds (*every unused fd is a leak waiting to happen*)
- **`execve()` semantics** — full path required, argv + envp conventions
- **`PATH` lookup** — reimplementing what the shell does transparently
- **Process lifecycle** — parent/child, `exit` codes (127 for "not found", 126 for "not executable")

---

<div align="center">

Built with ☕ at **42 School** · [github.com/Vavongg](https://github.com/Vavongg)

</div>
