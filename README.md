*This project has been created as part of the 42 curriculum by migusant.*

# Minishell Parsing

The **parsing module** of Minishell, developed as a standalone component before integration into the full shell. It implements the complete input processing pipeline — tokenization (lexer), syntax validation, variable expansion, quote handling, word splitting, and command structure building — producing ready-to-execute command lists from raw user input in C.

## Description

The Minishell Parsing project isolates the front-end of a bash-like shell interpreter, processing user input through a multi-stage pipeline: **lexing** (tokenization into words, operators, and redirections), **syntax checking** (validating token sequences), **expansion** (variable substitution, tilde, ANSI-C quoting), **word splitting** (splitting expanded variables on whitespace), **quote removal** (stripping outer quotes), and **parsing** (building linked lists of command structures with argument arrays and redirection chains). The module operates as a standalone shell loop with readline integration, signal handling, and debug output, but does not execute commands — it validates and structures input, then frees the result.

### Key Features

- **Lexer** tokenizes input into words, pipes, semicolons, and redirection operators (`<`, `>`, `>>`, `<<`) with quote-aware scanning
- **Syntax checker** validates token sequences before parsing (unclosed quotes, invalid operator combinations, consecutive redirections)
- **Parser** builds a linked list of `t_cmd` structures with argument arrays and `t_redir` redirection chains
- **Variable expansion** with `$VAR`, `$?` (exit code), tilde expansion (`~`), and `$'...'` ANSI-C quoting
- **Quote handling** with single quotes (literal), double quotes (with variable expansion), and nested quote processing
- **Word splitting** on expanded variables with quote-aware split logic and marking system
- **Heredoc delimiter marking** with expansion control based on whether the delimiter is quoted
- **Signal handling** with 4 modes: interactive (readline prompt), ignore, default, and heredoc (SIGINT closes stdin)
- **Environment variable lookup** via `ft_getenv()` operating on the raw `envp` array
- **Debug mode** (`MINISHELL_DEBUG`) for printing token lists and command structures at each pipeline stage
- **Proper resource cleanup** with separate parent and child cleanup paths to prevent leaks
- **Signal test scripts** for testing shell behavior with SIGQUIT, SIGTERM, SIGKILL, SIGABRT, SIGSEGV, SIGBUS, SIGFPE, SIGILL, and SIGPIPE
- **External functions reference** documenting all allowed system calls (readline, process management, signal handling, file operations)
- **Uses libft** as the authorized utility library including ft_printf and get_next_line

### Project Structure

```
├── includes/
│   └── parsing.h                           # Main header with all structures, enums, and prototypes
├── sources/
│   ├── main.c                              # Entry point, shell singleton, init, loop, and cleanup
│   ├── main_utils.c                        # Input validation (EOF, empty, whitespace-only)
│   ├── main_pipeline.c                     # Tokenize -> validate -> parse pipeline (no execution)
│   ├── main_debug.c                        # Debug printing for tokens and command lists
│   └── parsing/
│       ├── lexer/
│       │   ├── lexer.c                     # Main lexer loop, tokenization entry point
│       │   ├── lexer_helpers.c             # Token creation and linked list insertion
│       │   ├── lexer_checks.c              # Character classification (whitespace, special chars)
│       │   ├── lexer_utils.c               # Word extraction with quote-aware boundary detection
│       │   └── lexer_quotes.c              # Quoted section copying for token values
│       ├── syntax/
│       │   └── syntax_checker.c            # Token sequence validation (pipes, redirections, quotes)
│       ├── parser/
│       │   ├── parser.c                    # Command list builder from token stream
│       │   ├── parser_utils.c              # Single command parsing (args + redirections)
│       │   ├── parser_split_mark.c         # Marks tokens for word splitting after expansion
│       │   ├── parser_heredoc_mark.c       # Marks heredoc delimiters for expansion control
│       │   ├── parser_split_apply.c        # Applies word splitting on marked tokens
│       │   └── parser_split_apply_utils.c  # Quote-aware string splitting utility
│       ├── expander/
│       │   ├── expander.c                  # Token expansion orchestration and routing
│       │   ├── expander_quotes.c           # Single/double/ANSI-C quote expansion
│       │   ├── expander_substitutions.c    # $VAR, $?, tilde expansion
│       │   ├── expander_heredoc.c          # Variable expansion within heredoc lines
│       │   └── expander_utils.c            # String append helpers and variable lookup
│       ├── quotes/
│       │   ├── quote_removal.c             # Final quote stripping from expanded tokens
│       │   ├── quote_removal_utils.c       # Unquoted length counting and copying
│       │   ├── quote_removal_single.c      # Single quote removal logic
│       │   └── quote_removal_double.c      # Double quote removal logic
│       ├── signals/
│       │   └── signals.c                   # Signal setup (interactive, ignore, default, heredoc)
│       ├── environment/
│       │   └── environment.c               # ft_getenv() lookup on raw envp array
│       └── free.c                          # Token, command, and split array cleanup
├── tests/
│   ├── test_sigQUIT.sh                     # SIGQUIT signal test
│   ├── test_sigTERM.sh                     # SIGTERM signal test
│   ├── test_sigKILL.sh                     # SIGKILL signal test
│   ├── test_sigABRT.sh                     # SIGABRT signal test
│   ├── test_sigSEGV.sh                     # SIGSEGV signal test
│   ├── test_sigBUS.sh                      # SIGBUS signal test
│   ├── test_sigFPE.sh                      # SIGFPE signal test
│   ├── test_sigILL.sh                      # SIGILL signal test
│   ├── test_sigPIPE.sh                     # SIGPIPE signal test
│   ├── testers.txt                         # Comprehensive test cases for parsing validation
│   └── tests_jomunoz_pbongiov.txt          # Additional peer test cases
├── external_functions.md                   # Reference manual for all allowed external functions
├── en.subject.pdf                          # Original 42 project subject
├── libft/                                  # Custom C utility library (libft, ft_printf, get_next_line)
├── valgrind.supp                           # Valgrind suppression file for readline and system binary leaks
└── Makefile
```

## Instructions

### Compilation

```bash
make        # Compile the project (builds libft, then minishell)
make v      # Run with Valgrind (leak-check, fd tracking, child tracing, suppressions)
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Recompile from scratch
```

This produces the `minishell` executable (parsing-only mode — no command execution).

### Execution

```bash
./minishell         # Start the parsing shell with inherited environment
env -i ./minishell  # Start without environment variables
```

### Usage

The shell presents a `minishell$ ` prompt and processes input through the full parsing pipeline. With debug mode enabled (`MINISHELL_DEBUG = 1` in `parsing.h`), it prints the token list and command structures at each stage. Since this is the parsing module only, commands are parsed and structured but not executed.

```bash
# Input is tokenized, expanded, and parsed into command structures
ls -la | grep .c | wc -l
echo "Hello $USER"
cat << EOF
export VAR="value"
echo $HOME > output.txt
```

### Testing

Signal test scripts are provided in the `tests/` directory:

```bash
# Test signal handling behavior
./tests/test_sigQUIT.sh
./tests/test_sigTERM.sh
./tests/test_sigSEGV.sh
```

The `testers.txt` and `tests_jomunoz_pbongiov.txt` files contain comprehensive test cases for validating parsing behavior against bash.

## Technical Implementation

### Parsing Pipeline Architecture

User input flows through a multi-stage processing pipeline:

```
Input -> Lexer -> Syntax Check -> Expander -> Word Split -> Quote Removal -> Parser -> Command List
                                                 |              |
                                           Heredoc Mark    Word Split
                                            Expansion       Marking
```

1. **Lexer:** Scans input character by character, producing a linked list of `t_token` nodes (WORD, PIPE, SEMICOLON, REDIR_IN, REDIR_OUT, REDIR_APPEND, REDIR_HEREDOC). Handles quoted strings as single tokens, including backslash counting for escape detection.

2. **Syntax Checker:** Validates token sequences — rejects unclosed quotes, pipes at start/end, consecutive operators, and redirections without targets. Sets exit code to 2 on syntax errors (matching bash behavior).

3. **Expander:** Processes each token for variable substitution (`$VAR`, `$?`), tilde expansion (`~` to `$HOME`), single/double quote content handling, and ANSI-C quoting (`$'...'`). Heredoc delimiters are skipped to preserve literal matching. Removes empty word tokens after expansion.

4. **Word Splitting:** Two-phase system — first marks tokens that resulted from variable expansion (`wd_split` flag), then splits those tokens on whitespace boundaries using a quote-aware split algorithm.

5. **Heredoc Marking:** Identifies heredoc delimiters and sets the `hd_expand` flag based on whether the delimiter contains quotes (quoted delimiters suppress variable expansion in heredoc content).

6. **Quote Removal:** Strips outer quotes from expanded tokens while preserving quoted content. Handles single and double quotes separately with proper nesting.

7. **Parser:** Converts the token list into a linked list of `t_cmd` structures, each containing an argument array (`char **args`) and a redirection chain (`t_redir` linked list with type, filename, fd, and expansion flag).

### Data Structures

```
t_shell (singleton)
├── envp        → char** (raw environment from main)
├── toks        → t_token linked list
│                  ├── type (WORD, PIPE, REDIR_*, ...)
│                  ├── value (string content)
│                  ├── hd_expand (heredoc expansion flag)
│                  ├── wd_split (word split flag)
│                  └── next
├── cmds        → t_cmd linked list
│                  ├── args (char** argument array)
│                  ├── redirections → t_redir linked list
│                  │                   ├── type, file, fd, hd_expand
│                  │                   └── next
│                  └── next
└── exit_code   → int (last command exit status)
```

### Differences from Full Minishell

This parsing module differs from the integrated minishell in several ways:

| Aspect | Parsing Module | Full Minishell |
|--------|---------------|----------------|
| Environment | Raw `char **envp` from main | `t_env` linked list with get/set/unset |
| Shell struct | No `should_exit` flag | Includes `should_exit` for exit builtin |
| Execution | Commands parsed and freed (no execution) | Full executor with builtins, pipes, redirections |
| Source dir | `sources/` | `src/` |
| Header | `parsing.h` | `minishell.h` |

### Signal Handling

| Mode | SIGINT (Ctrl+C) | SIGQUIT (Ctrl+\) | Context |
|------|------------------|-------------------|---------|
| Interactive | New prompt line (`rl_replace_line` + `rl_redisplay`), exit code 130 | Ignored | Waiting for user input |
| Ignore | Ignored | Ignored | During child process execution |
| Default | Default behavior (terminate) | Default behavior (core dump) | Inside child processes |
| Heredoc | Closes stdin to break readline loop | Ignored | Inside heredoc child process |

## Resources

### Shell & Bash Reference

- `man bash(1)` — Bash reference manual (quoting, expansion, redirections)
- [Bash Reference Manual (GNU)](https://www.gnu.org/software/bash/manual/bash.html) — Comprehensive bash documentation
- [POSIX Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) — Shell specification
- [devhints.io/bash](https://devhints.io/bash) — Bash cheat sheet

### Compiler Theory

- *Lex & Yacc* 2nd Edition, O'Reilly Media — Tony Mason & Doug Brown — Lexer and parser design patterns

### Signal Handling

- `man signal(2)` — Signal disposition
- `man sigaction(2)` — Signal action configuration

### Readline Library

- `man readline(3)` — Line reading with editing
- `man add_history(3)` — Command history management
- `rl_on_new_line`, `rl_replace_line`, `rl_redisplay` — Prompt redisplay after signal

### Debugging Tools

- `man valgrind(1)` — Memory error detection
- [Valgrind Manual](https://valgrind.org/docs/manual/manual.html) — Leak checking and fd tracking

### AI Usage

AI tools (GitHub Copilot, ChatGPT) were used as a **thinking partner and debugging assistant** to discuss problems and approaches, but all final code, architecture decisions, and bug fixes were produced by the student after understanding the underlying concepts.

**Documentation & Understanding:**
- Explaining bash tokenization rules, quoting semantics, and expansion order
- Clarifying word splitting behavior and its interaction with variable expansion
- Understanding heredoc delimiter quoting and its effect on content expansion
- Discussing signal handling in interactive shell environments
- Refining and structuring README.md documentation to accurately represent technical implementations

**Code Review:**
- Reviewing quote removal logic for edge cases with nested and mixed quotes
- Identifying potential memory leaks in token expansion paths
- Verifying syntax checker coverage for all invalid token combinations

**Learning Resources:**
- Providing reference for POSIX shell behavior and bash-specific extensions
- Clarifying readline library integration and signal interaction
- Explaining lexer/parser design patterns from compiler theory

**Testing Assistance & Debugging:**
- Helping design test cases for edge scenarios (empty expansions, nested quotes, consecutive operators)
- Debugging signal handling with readline prompt redisplay
- Identifying memory leaks via Valgrind suppression patterns for readline

## License

This project is part of the 42 Common Core curriculum. See [LICENSE](LICENSE) for details.
