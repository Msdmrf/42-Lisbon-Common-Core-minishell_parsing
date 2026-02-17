# External Functions Manual - Minishell Project (42 School)

## Table of Contents
1. [Readline Library Functions](#readline-library-functions)
2. [Standard I/O Functions](#standard-io-functions)
3. [Memory Management Functions](#memory-management-functions)
4. [File Operations Functions](#file-operations-functions)
5. [Process Management Functions](#process-management-functions)
6. [Signal Handling Functions](#signal-handling-functions)
7. [Directory Operations Functions](#directory-operations-functions)
8. [Error Handling Functions](#error-handling-functions)
9. [Terminal Control Functions](#terminal-control-functions)
10. [Environment Functions](#environment-functions)
11. [Termcap Library Functions](#termcap-library-functions)

---

## Readline Library Functions

### 1. readline

**Prototype:**
```c
char *readline(const char *prompt);
```

**Description:**
Reads a line from the terminal with editing capabilities and displays a prompt. This is the primary function for interactive input in a shell.

**Input Arguments:**
- `prompt`: A string to display as a prompt before reading input (can be NULL)

**Return Value:**
- Returns a pointer to a malloc'd string containing the line read (without the newline)
- Returns NULL on EOF or error

**Extra Information:**
- Essential for minishell's interactive mode
- The returned string must be freed by the caller
- Supports command-line editing (arrow keys, backspace, etc.)
- Link with `-lreadline` flag

---

### 2. rl_clear_history

**Prototype:**
```c
void rl_clear_history(void);
```

**Description:**
Clears the entire command history maintained by readline.

**Input Arguments:**
- None

**Return Value:**
- None (void function)

**Extra Information:**
- Useful when you need to reset the history (e.g., when exiting the shell)
- Frees all memory associated with the history list

---

### 3. rl_on_new_line

**Prototype:**
```c
int rl_on_new_line(void);
```

**Description:**
Tells readline that the cursor has been moved to a new line. Used to update readline's internal state.

**Input Arguments:**
- None

**Return Value:**
- Returns 0 on success

**Extra Information:**
- Important for signal handling (e.g., when Ctrl+C creates a new prompt)
- Used in conjunction with rl_replace_line and rl_redisplay

---

### 4. rl_replace_line

**Prototype:**
```c
void rl_replace_line(const char *text, int clear_undo);
```

**Description:**
Replaces the current line buffer with the specified text.

**Input Arguments:**
- `text`: The new text to place in the line buffer
- `clear_undo`: If non-zero, clears the undo list associated with the current line

**Return Value:**
- None (void function)

**Extra Information:**
- Useful for implementing signal handlers that need to clear the current input
- Often used with empty string to clear the line after Ctrl+C

---

### 5. rl_redisplay

**Prototype:**
```c
void rl_redisplay(void);
```

**Description:**
Forces readline to redisplay the current line buffer on the screen.

**Input Arguments:**
- None

**Return Value:**
- None (void function)

**Extra Information:**
- Essential after signal handling to refresh the prompt
- Used after rl_on_new_line and rl_replace_line to show a clean prompt

---

### 6. add_history

**Prototype:**
```c
void add_history(const char *line);
```

**Description:**
Adds a line to the command history list.

**Input Arguments:**
- `line`: The command string to add to history

**Return Value:**
- None (void function)

**Extra Information:**
- Should be called for non-empty commands
- Allows users to access previous commands with up/down arrows
- Duplicates can be added; filtering is up to you

---

## Standard I/O Functions

### 7. printf

**Prototype:**
```c
int printf(const char *format, ...);
```

**Description:**
Prints formatted output to standard output (stdout).

**Input Arguments:**
- `format`: A format string containing text and format specifiers
- `...`: Variable number of arguments corresponding to format specifiers

**Return Value:**
- Returns the number of characters printed (excluding null byte)
- Returns a negative value on error

**Extra Information:**
- Useful for debugging and error messages
- Use write() for more precise output control in production code

---

### 8. write

**Prototype:**
```c
ssize_t write(int fd, const void *buf, size_t count);
```

**Description:**
Writes up to count bytes from the buffer to the file descriptor.

**Input Arguments:**
- `fd`: File descriptor to write to (1 for stdout, 2 for stderr)
- `buf`: Pointer to the buffer containing data to write
- `count`: Number of bytes to write

**Return Value:**
- Returns the number of bytes actually written
- Returns -1 on error (sets errno)

**Extra Information:**
- Preferred over printf for actual shell output
- May write fewer bytes than requested (check return value)
- Used for redirections and pipe operations

---

## Memory Management Functions

### 9. malloc

**Prototype:**
```c
void *malloc(size_t size);
```

**Description:**
Allocates a block of memory of the specified size on the heap.

**Input Arguments:**
- `size`: Number of bytes to allocate

**Return Value:**
- Returns a pointer to the allocated memory
- Returns NULL if allocation fails

**Extra Information:**
- Memory is uninitialized (contains garbage values)
- Always check for NULL return
- Must be freed with free() to avoid memory leaks
- Critical for dynamic string handling and command parsing

---

### 10. free

**Prototype:**
```c
void free(void *ptr);
```

**Description:**
Frees previously allocated memory.

**Input Arguments:**
- `ptr`: Pointer to memory block to free (can be NULL)

**Return Value:**
- None (void function)

**Extra Information:**
- Calling free(NULL) is safe and does nothing
- Freeing the same pointer twice causes undefined behavior
- Essential for avoiding memory leaks
- Use valgrind to check for leaks

---

## File Operations Functions

### 11. access

**Prototype:**
```c
int access(const char *pathname, int mode);
```

**Description:**
Checks whether the calling process can access the file pathname.

**Input Arguments:**
- `pathname`: Path to the file to check
- `mode`: Accessibility check(s) to perform:
  - `F_OK`: File exists
  - `R_OK`: Read permission
  - `W_OK`: Write permission
  - `X_OK`: Execute permission

**Return Value:**
- Returns 0 if all checks succeed
- Returns -1 on error (sets errno)

**Extra Information:**
- Useful for checking if a command exists in PATH directories
- Check X_OK to verify if a file is executable
- Subject to race conditions (file status can change after check)

---

### 12. open

**Prototype:**
```c
int open(const char *pathname, int flags, mode_t mode);
```

**Description:**
Opens a file and returns a file descriptor.

**Input Arguments:**
- `pathname`: Path to the file
- `flags`: File access mode and flags:
  - `O_RDONLY`: Read only
  - `O_WRONLY`: Write only
  - `O_RDWR`: Read and write
  - `O_CREAT`: Create if doesn't exist
  - `O_TRUNC`: Truncate to zero length
  - `O_APPEND`: Append mode
- `mode`: Permissions if creating file (e.g., 0644)

**Return Value:**
- Returns file descriptor (non-negative integer) on success
- Returns -1 on error (sets errno)

**Extra Information:**
- Essential for implementing redirections (>, >>, <)
- Remember to close() the file descriptor
- File descriptor 0=stdin, 1=stdout, 2=stderr

---

### 13. read

**Prototype:**
```c
ssize_t read(int fd, void *buf, size_t count);
```

**Description:**
Reads up to count bytes from a file descriptor into a buffer.

**Input Arguments:**
- `fd`: File descriptor to read from
- `buf`: Buffer to store the read data
- `count`: Maximum number of bytes to read

**Return Value:**
- Returns number of bytes read
- Returns 0 on EOF
- Returns -1 on error (sets errno)

**Extra Information:**
- May read fewer bytes than requested
- Used for reading from files, pipes, or stdin
- Blocking call by default

---

### 14. close

**Prototype:**
```c
int close(int fd);
```

**Description:**
Closes a file descriptor.

**Input Arguments:**
- `fd`: File descriptor to close

**Return Value:**
- Returns 0 on success
- Returns -1 on error (sets errno)

**Extra Information:**
- Always close file descriptors when done
- Closing an already closed fd causes error
- Important for avoiding file descriptor leaks
- Especially critical after dup2() operations

---

### 15. unlink

**Prototype:**
```c
int unlink(const char *pathname);
```

**Description:**
Deletes a file from the filesystem.

**Input Arguments:**
- `pathname`: Path to the file to delete

**Return Value:**
- Returns 0 on success
- Returns -1 on error (sets errno)

**Extra Information:**
- Used to remove temporary files (e.g., heredoc temp files)
- File must be closed before unlinking
- Only removes the link; file deleted when all handles closed

---

## Process Management Functions

### 16. fork

**Prototype:**
```c
pid_t fork(void);
```

**Description:**
Creates a new process by duplicating the calling process.

**Input Arguments:**
- None

**Return Value:**
- Returns 0 in the child process
- Returns child's PID in the parent process
- Returns -1 on error (sets errno)

**Extra Information:**
- Fundamental for executing commands
- Child inherits copies of parent's file descriptors
- Child should call execve() to run a new program
- Parent should call wait() to avoid zombies

---

### 17. wait

**Prototype:**
```c
pid_t wait(int *status);
```

**Description:**
Waits for any child process to change state.

**Input Arguments:**
- `status`: Pointer to store child's exit status (can be NULL)

**Return Value:**
- Returns PID of terminated child on success
- Returns -1 on error (sets errno)

**Extra Information:**
- Blocks until a child terminates
- Use WIFEXITED(status) and WEXITSTATUS(status) macros
- Prevents zombie processes

---

### 18. waitpid

**Prototype:**
```c
pid_t waitpid(pid_t pid, int *status, int options);
```

**Description:**
Waits for a specific child process to change state.

**Input Arguments:**
- `pid`: Process ID to wait for:
  - `> 0`: Wait for specific child
  - `0`: Wait for any child in same process group
  - `-1`: Wait for any child (same as wait())
  - `< -1`: Wait for any child in process group |pid|
- `status`: Pointer to store exit status (can be NULL)
- `options`: Options like `WNOHANG` (don't block)

**Return Value:**
- Returns PID of child on success
- Returns 0 if WNOHANG and no child changed state
- Returns -1 on error (sets errno)

**Extra Information:**
- More flexible than wait()
- Useful for waiting on specific commands in pipelines
- Check exit status to set $? variable

---

### 19. wait3

**Prototype:**
```c
pid_t wait3(int *status, int options, struct rusage *rusage);
```

**Description:**
Similar to waitpid(-1, status, options) but also returns resource usage information.

**Input Arguments:**
- `status`: Pointer to store exit status
- `options`: Wait options (e.g., WNOHANG, WUNTRACED)
- `rusage`: Pointer to receive resource usage info (can be NULL)

**Return Value:**
- Returns PID of terminated child on success
- Returns 0 if WNOHANG and no child available
- Returns -1 on error (sets errno)

**Extra Information:**
- Obsolete; use waitpid() for basic functionality
- Resource usage info rarely needed for minishell

---

### 20. wait4

**Prototype:**
```c
pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);
```

**Description:**
Waits for a specific child and optionally returns resource usage.

**Input Arguments:**
- `pid`: Process ID to wait for (same semantics as waitpid)
- `status`: Pointer to store exit status
- `options`: Wait options
- `rusage`: Pointer to receive resource usage info (can be NULL)

**Return Value:**
- Returns PID of terminated child on success
- Returns 0 if WNOHANG and no child available
- Returns -1 on error (sets errno)

**Extra Information:**
- Combines waitpid() functionality with resource usage
- Generally waitpid() is sufficient for minishell

---

### 21. execve

**Prototype:**
```c
int execve(const char *pathname, char *const argv[], char *const envp[]);
```

**Description:**
Executes a program, replacing the current process image.

**Input Arguments:**
- `pathname`: Absolute or relative path to the executable
- `argv`: Array of argument strings (NULL-terminated), argv[0] should be filename
- `envp`: Array of environment strings "KEY=value" (NULL-terminated)

**Return Value:**
- Does not return on success (process is replaced)
- Returns -1 on error (sets errno)

**Extra Information:**
- Called in child process after fork()
- Must construct argv array: {command, arg1, arg2, ..., NULL}
- Must handle PATH searching yourself
- If execve returns, an error occurred

---

### 22. exit

**Prototype:**
```c
void exit(int status);
```

**Description:**
Terminates the calling process with the specified exit status.

**Input Arguments:**
- `status`: Exit status code (0 = success, non-zero = error)

**Return Value:**
- Does not return

**Extra Information:**
- Use in child process if execve fails
- Main shell process should not call exit (use return from main)
- Exit status is available to parent via wait functions
- Status is masked to 0-255

---

## Signal Handling Functions

### 23. signal

**Prototype:**
```c
sighandler_t signal(int signum, sighandler_t handler);
```

**Description:**
Sets a signal handler for the specified signal.

**Input Arguments:**
- `signum`: Signal number (e.g., SIGINT, SIGQUIT)
- `handler`: Function pointer to handler, or:
  - `SIG_DFL`: Default action
  - `SIG_IGN`: Ignore signal

**Return Value:**
- Returns previous signal handler on success
- Returns SIG_ERR on error (sets errno)

**Extra Information:**
- Less reliable than sigaction()
- Consider using sigaction() instead for portability
- Needed to handle Ctrl+C (SIGINT) and Ctrl+\ (SIGQUIT)

---

### 24. sigaction

**Prototype:**
```c
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
```

**Description:**
Examines and changes the action taken on receipt of a specific signal.

**Input Arguments:**
- `signum`: Signal number
- `act`: Pointer to new sigaction structure (can be NULL)
- `oldact`: Pointer to store old action (can be NULL)

**Return Value:**
- Returns 0 on success
- Returns -1 on error (sets errno)

**Extra Information:**
- More reliable and portable than signal()
- Use for handling SIGINT (Ctrl+C) in interactive mode
- SIGQUIT (Ctrl+\) should be ignored in interactive mode
- Essential for proper signal handling in minishell

---

### 25. sigemptyset

**Prototype:**
```c
int sigemptyset(sigset_t *set);
```

**Description:**
Initializes a signal set to be empty (no signals).

**Input Arguments:**
- `set`: Pointer to signal set to initialize

**Return Value:**
- Returns 0 on success
- Returns -1 on error

**Extra Information:**
- Must be called before using a sigset_t
- Used with sigaction to configure signal masks
- Always initialize signal sets before use

---

### 26. sigaddset

**Prototype:**
```c
int sigaddset(sigset_t *set, int signum);
```

**Description:**
Adds a signal to a signal set.

**Input Arguments:**
- `set`: Pointer to signal set
- `signum`: Signal number to add

**Return Value:**
- Returns 0 on success
- Returns -1 on error

**Extra Information:**
- Used after sigemptyset to build a signal mask
- Useful for blocking specific signals during critical sections

---

### 27. kill

**Prototype:**
```c
int kill(pid_t pid, int sig);
```

**Description:**
Sends a signal to a process or group of processes.

**Input Arguments:**
- `pid`: Process ID:
  - `> 0`: Send to specific process
  - `0`: Send to all processes in current group
  - `-1`: Send to all processes (with permission)
  - `< -1`: Send to process group |pid|
- `sig`: Signal number to send (0 to test if process exists)

**Return Value:**
- Returns 0 on success
- Returns -1 on error (sets errno)

**Extra Information:**
- Useful for implementing job control
- kill(pid, 0) tests if process exists without sending signal
- May need for handling Ctrl+C in child processes

---

## Directory Operations Functions

### 28. getcwd

**Prototype:**
```c
char *getcwd(char *buf, size_t size);
```

**Description:**
Gets the current working directory path.

**Input Arguments:**
- `buf`: Buffer to store path (can be NULL)
- `size`: Size of buffer

**Return Value:**
- Returns pointer to current directory path
- If buf is NULL, returns malloc'd string (must be freed)
- Returns NULL on error (sets errno)

**Extra Information:**
- Essential for implementing pwd builtin
- Needed to update PWD environment variable
- If buf is NULL, function allocates memory for you

---

### 29. chdir

**Prototype:**
```c
int chdir(const char *path);
```

**Description:**
Changes the current working directory to the specified path.

**Input Arguments:**
- `path`: Path to new directory (absolute or relative)

**Return Value:**
- Returns 0 on success
- Returns -1 on error (sets errno)

**Extra Information:**
- Essential for implementing cd builtin
- Must be called in parent process (not child)
- Update PWD and OLDPWD environment variables after successful change
- Handle special cases: "cd", "cd ~", "cd -"

---

### 30. opendir

**Prototype:**
```c
DIR *opendir(const char *name);
```

**Description:**
Opens a directory stream for reading directory entries.

**Input Arguments:**
- `name`: Path to directory

**Return Value:**
- Returns pointer to DIR structure on success
- Returns NULL on error (sets errno)

**Extra Information:**
- Used if implementing wildcards or directory listing
- Must be closed with closedir()
- May not be needed for basic minishell

---

### 31. readdir

**Prototype:**
```c
struct dirent *readdir(DIR *dirp);
```

**Description:**
Reads the next directory entry from a directory stream.

**Input Arguments:**
- `dirp`: Directory stream pointer from opendir()

**Return Value:**
- Returns pointer to dirent structure on success
- Returns NULL at end of directory or on error

**Extra Information:**
- Use d_name field of struct dirent for entry name
- Returns "." and ".." entries
- Useful for PATH searching or wildcard expansion

---

### 32. closedir

**Prototype:**
```c
int closedir(DIR *dirp);
```

**Description:**
Closes a directory stream.

**Input Arguments:**
- `dirp`: Directory stream pointer to close

**Return Value:**
- Returns 0 on success
- Returns -1 on error (sets errno)

**Extra Information:**
- Must be called for every opendir()
- Prevents resource leaks

---

## File Status Functions

### 33. stat

**Prototype:**
```c
int stat(const char *pathname, struct stat *statbuf);
```

**Description:**
Gets file status information about the specified file.

**Input Arguments:**
- `pathname`: Path to file
- `statbuf`: Pointer to stat structure to fill

**Return Value:**
- Returns 0 on success
- Returns -1 on error (sets errno)

**Extra Information:**
- Follows symbolic links
- Use S_ISDIR(statbuf.st_mode) to check if directory
- Use S_ISREG(statbuf.st_mode) to check if regular file
- Useful for checking file type and permissions

---

### 34. lstat

**Prototype:**
```c
int lstat(const char *pathname, struct stat *statbuf);
```

**Description:**
Like stat(), but does not follow symbolic links.

**Input Arguments:**
- `pathname`: Path to file
- `statbuf`: Pointer to stat structure to fill

**Return Value:**
- Returns 0 on success
- Returns -1 on error (sets errno)

**Extra Information:**
- Returns information about the link itself, not the target
- Use when you need to detect symbolic links

---

### 35. fstat

**Prototype:**
```c
int fstat(int fd, struct stat *statbuf);
```

**Description:**
Gets file status information using a file descriptor.

**Input Arguments:**
- `fd`: Open file descriptor
- `statbuf`: Pointer to stat structure to fill

**Return Value:**
- Returns 0 on success
- Returns -1 on error (sets errno)

**Extra Information:**
- Useful when you already have an open file descriptor
- Cannot fail due to path issues

---

## Error Handling Functions

### 36. strerror

**Prototype:**
```c
char *strerror(int errnum);
```

**Description:**
Returns a string describing the error code.

**Input Arguments:**
- `errnum`: Error number (usually from errno)

**Return Value:**
- Returns pointer to error message string
- String should not be modified or freed

**Extra Information:**
- Use with errno to get error descriptions
- Example: strerror(errno) after system call fails
- Useful for user-friendly error messages

---

### 37. perror

**Prototype:**
```c
void perror(const char *s);
```

**Description:**
Prints an error message to stderr based on errno.

**Input Arguments:**
- `s`: Prefix string to print before error message (can be NULL)

**Return Value:**
- None (void function)

**Extra Information:**
- Automatically includes strerror(errno)
- Format: "prefix: error message"
- Convenient for quick error reporting
- Consider using write() + strerror() for more control

---

## File Descriptor Functions

### 38. dup

**Prototype:**
```c
int dup(int oldfd);
```

**Description:**
Duplicates a file descriptor, creating a new descriptor that refers to the same open file.

**Input Arguments:**
- `oldfd`: File descriptor to duplicate

**Return Value:**
- Returns new file descriptor on success (lowest available fd)
- Returns -1 on error (sets errno)

**Extra Information:**
- New fd shares same file offset and flags
- Both descriptors must be closed separately
- Useful for saving stdin/stdout before redirections

---

### 39. dup2

**Prototype:**
```c
int dup2(int oldfd, int newfd);
```

**Description:**
Duplicates a file descriptor to a specific descriptor number.

**Input Arguments:**
- `oldfd`: File descriptor to duplicate
- `newfd`: Desired file descriptor number

**Return Value:**
- Returns newfd on success
- Returns -1 on error (sets errno)

**Extra Information:**
- If newfd is open, it's closed first (atomically)
- Essential for implementing redirections
- Example: dup2(file_fd, STDOUT_FILENO) redirects stdout to file
- Critical for pipe implementation

---

### 40. pipe

**Prototype:**
```c
int pipe(int pipefd[2]);
```

**Description:**
Creates a unidirectional pipe for inter-process communication.

**Input Arguments:**
- `pipefd`: Array of 2 integers to receive file descriptors
  - `pipefd[0]`: Read end of pipe
  - `pipefd[1]`: Write end of pipe

**Return Value:**
- Returns 0 on success
- Returns -1 on error (sets errno)

**Extra Information:**
- Essential for implementing pipelines (|)
- Data written to pipefd[1] can be read from pipefd[0]
- Close unused ends in child processes
- Blocking: read blocks until data available, write blocks if pipe full

---

## Terminal Control Functions

### 41. isatty

**Prototype:**
```c
int isatty(int fd);
```

**Description:**
Tests whether a file descriptor refers to a terminal.

**Input Arguments:**
- `fd`: File descriptor to test

**Return Value:**
- Returns 1 if fd is a terminal
- Returns 0 if not a terminal or on error

**Extra Information:**
- Use to determine if running interactively
- Check stdin to decide whether to display prompt
- Useful for differentiating interactive vs script mode

---

### 42. ttyname

**Prototype:**
```c
char *ttyname(int fd);
```

**Description:**
Returns the name of the terminal associated with a file descriptor.

**Input Arguments:**
- `fd`: File descriptor

**Return Value:**
- Returns pointer to terminal name (e.g., "/dev/pts/0")
- Returns NULL on error

**Extra Information:**
- Rarely needed for minishell
- String should not be freed (static buffer)

---

### 43. ttyslot

**Prototype:**
```c
int ttyslot(void);
```

**Description:**
Returns the index of the current user's terminal entry in some system files.

**Input Arguments:**
- None

**Return Value:**
- Returns slot number on success
- Returns 0 on error or if not attached to a terminal

**Extra Information:**
- Obsolete function
- Unlikely to be needed for minishell

---

### 44. ioctl

**Prototype:**
```c
int ioctl(int fd, unsigned long request, ...);
```

**Description:**
Performs device-specific I/O operations and other operations which cannot be expressed by regular system calls.

**Input Arguments:**
- `fd`: File descriptor
- `request`: Device-dependent request code
- `...`: Optional argument (usually a pointer)

**Return Value:**
- Return value depends on request
- Returns -1 on error (sets errno)

**Extra Information:**
- May be used for terminal control (e.g., getting terminal size)
- TIOCGWINSZ request gets window size
- Generally not required for basic minishell

---

### 45. tcsetattr

**Prototype:**
```c
int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);
```

**Description:**
Sets the terminal attributes.

**Input Arguments:**
- `fd`: File descriptor (terminal)
- `optional_actions`: When to apply changes:
  - `TCSANOW`: Immediately
  - `TCSADRAIN`: After output drained
  - `TCSAFLUSH`: After output drained, flush input
- `termios_p`: Pointer to termios structure with new settings

**Return Value:**
- Returns 0 on success
- Returns -1 on error (sets errno)

**Extra Information:**
- Used to configure terminal behavior (e.g., raw mode)
- May be needed for advanced line editing
- Typically used with tcgetattr()

---

### 46. tcgetattr

**Prototype:**
```c
int tcgetattr(int fd, struct termios *termios_p);
```

**Description:**
Gets the current terminal attributes.

**Input Arguments:**
- `fd`: File descriptor (terminal)
- `termios_p`: Pointer to termios structure to fill

**Return Value:**
- Returns 0 on success
- Returns -1 on error (sets errno)

**Extra Information:**
- Use before tcsetattr() to save current settings
- Allows restoring terminal state later
- Important for terminal control

---

## Environment Functions

### 47. getenv

**Prototype:**
```c
char *getenv(const char *name);
```

**Description:**
Gets the value of an environment variable.

**Input Arguments:**
- `name`: Name of environment variable (e.g., "PATH", "HOME")

**Return Value:**
- Returns pointer to value string on success
- Returns NULL if variable not found

**Extra Information:**
- Essential for accessing PATH, HOME, etc.
- Returned string should not be modified or freed
- Alternative: parse envp array from main() or maintain your own environment

---

## Termcap Library Functions

### 48. tgetent

**Prototype:**
```c
int tgetent(char *bp, const char *name);
```

**Description:**
Loads the termcap entry for the terminal type specified by name.

**Input Arguments:**
- `bp`: Buffer for termcap entry (can be NULL)
- `name`: Terminal type name (e.g., value of TERM environment variable)

**Return Value:**
- Returns 1 on success
- Returns 0 if no entry found
- Returns -1 if termcap database not found

**Extra Information:**
- Must be called before other termcap functions
- Link with `-ltermcap` or `-lncurses`
- May not be needed if only using readline

---

### 49. tgetflag

**Prototype:**
```c
int tgetflag(const char *id);
```

**Description:**
Gets a boolean capability from the termcap entry.

**Input Arguments:**
- `id`: Two-character capability name

**Return Value:**
- Returns 1 if capability is present
- Returns 0 if capability is not present

**Extra Information:**
- Must call tgetent() first
- Used for terminal capability queries

---

### 50. tgetnum

**Prototype:**
```c
int tgetnum(const char *id);
```

**Description:**
Gets a numeric capability from the termcap entry.

**Input Arguments:**
- `id`: Two-character capability name

**Return Value:**
- Returns numeric value of capability
- Returns -1 if capability is not present

**Extra Information:**
- Must call tgetent() first
- Example: "co" for number of columns, "li" for lines

---

### 51. tgetstr

**Prototype:**
```c
char *tgetstr(const char *id, char **area);
```

**Description:**
Gets a string capability from the termcap entry.

**Input Arguments:**
- `id`: Two-character capability name
- `area`: Pointer to buffer pointer (can be NULL)

**Return Value:**
- Returns pointer to capability string
- Returns NULL if capability not found

**Extra Information:**
- Must call tgetent() first
- If area is not NULL, string is copied to buffer and pointer advanced
- Example capabilities: "cl" (clear screen), "ce" (clear to end of line)

---

### 52. tgoto

**Prototype:**
```c
char *tgoto(const char *cap, int col, int row);
```

**Description:**
Instantiates parameters for cursor movement capability strings.

**Input Arguments:**
- `cap`: Cursor movement capability string from tgetstr()
- `col`: Column number
- `row`: Row number

**Return Value:**
- Returns pointer to formatted string

**Extra Information:**
- Used with cursor movement capabilities
- Pass result to tputs()
- May not be needed for basic minishell

---

### 53. tputs

**Prototype:**
```c
int tputs(const char *str, int affcnt, int (*putc)(int));
```

**Description:**
Outputs a termcap string, applying padding if necessary.

**Input Arguments:**
- `str`: Termcap string to output
- `affcnt`: Number of lines affected (for padding calculation)
- `putc`: Function to output each character

**Return Value:**
- Returns 0 on success (typically)

**Extra Information:**
- Used to output strings from tgetstr() or tgoto()
- Handles padding delays
- putc function should return the character or EOF

---

## Summary for Minishell Project

### Critical Functions for Core Functionality:
- **Input**: readline, add_history, rl_clear_history
- **Parsing & Execution**: fork, execve, wait/waitpid
- **Redirections**: open, close, dup2
- **Pipes**: pipe
- **Builtins**: chdir, getcwd, getenv
- **Signals**: sigaction, sigemptyset, sigaddset
- **Memory**: malloc, free
- **I/O**: read, write

### Important Functions for Polish:
- **Error Handling**: strerror, perror
- **Signal Handling**: rl_on_new_line, rl_replace_line, rl_redisplay
- **File Checks**: access, stat

### Less Commonly Used:
- **Termcap functions** (if not using readline exclusively)
- **wait3, wait4** (waitpid is usually sufficient)
- **ttyslot, ttyname** (rarely needed)

---

## Best Practices

1. **Always check return values** - Most functions return -1 or NULL on error
2. **Check errno** - Use strerror(errno) or perror() for error messages
3. **Free all malloc'd memory** - Including strings from readline()
4. **Close all file descriptors** - Especially important for pipes and redirections
5. **Handle signals properly** - Use sigaction over signal
6. **Clean up on exit** - Call rl_clear_history(), close fds, free memory
7. **Test with valgrind** - Ensure no memory leaks or invalid reads/writes

---

## Useful Macros

### Wait Status Macros:
```c
WIFEXITED(status)    // True if child exited normally
WEXITSTATUS(status)  // Extract exit status
WIFSIGNALED(status)  // True if child terminated by signal
WTERMSIG(status)     // Get signal number that terminated child
```

### File Descriptor Numbers:
```c
STDIN_FILENO   // 0
STDOUT_FILENO  // 1
STDERR_FILENO  // 2
```

### File Permission Modes:
```c
S_ISREG(m)  // Is regular file
S_ISDIR(m)  // Is directory
S_ISLNK(m)  // Is symbolic link
```

---

## Compilation Flags

```bash
# Basic compilation
gcc -Wall -Wextra -Werror minishell.c -lreadline

# With additional libraries if needed
gcc -Wall -Wextra -Werror minishell.c -lreadline -ltermcap
```