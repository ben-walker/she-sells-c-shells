# she-sells-c-shells
Shell process written in C

### Solution Report
My approach was to write small, self-contained modules for each part of the system, and slowly connect them/write required interconnective code. For example: I started with a `prompt` library that would fill in a `struct Prompt` with relevant data for constructing the user's prompt (i.e. machine name, user name, and their root status). A `while (true)` loop handles all user input until an `exit` is encountered.

I decided to have separate functions within the same library that would run based on the `pid` of the process (i.e. parent or child). The parent would then determine if the task was to be run in the background, and if it was return immediately (rather than wait for the child to finish). This worked pretty smoothly - the child's task was to "sanitize" the arguments given to it by the user. This meant process all file redirection/background arguments, then strip them from the argument array and return that new array. I wrote all the built-ins (`args`, `gcd`, and `rand`) as plugins that would be consumed by the `internal` library (which in turn is called from the child process). This simplified the code for the child, and allowed me to simply call `runInternal(args)` and forget about it.

The most difficult part was managing running processes. I settled on a static linked list (see `processList.c`) that acts as the running process `state` for the entire shell. This list had to be static so that it could be acted on by the `SIGCHLD` signal handler (you can't pass data to a signal handler, and there's a very limited list of functions that are safe to call from them). Here's the general concept for the management of the process list: When a command is run (foreground or background), add it to the list in `Open` state from the parent process. When the SIGCHLD handler is run, mark the process that triggered the SIGCHLD signal as `Closed`. On the next iteration of the shell, cycle through the `Closed` processes, print that they've finished, then remove them from the list.

### Running the Shell
**Note:** You'll need `flex` installed to compile it
1. Run `make` in the base directory
2. Type `./tusk`

### Built-in Commands
* **`exit`**
  * Stops the shell process
* **`gcd`**
  * Compute the greatest common divisor of two numbers (decimal or hexadecimal)
  * Usage: `gcd [number1] [number2]`
  * Examples: `gcd 8 37`, `gcd 5 50`, `gcd 0xc 12`
* **`args`**
  * Count and list command line arguments.
  * Note: background and file redirection arguments are ignored.
  * Examples: `args 1 2 3 4 "five, six"`, `args test new 1 2`
* **`rand`**
  * Compute a random number in a `min`/`max` range
  * Usage: `rand [min] [max]`
  * Note: the min and max args are optional; users can supply one, none, or both
  * Examples: `rand`, `rand 5000`, `rand 10 20`

### File Redirection
**Note:** Built-in commands only support output redirection; `args`, `rand`, and `gcd` will not process a file redirected as `stdin`
* Redirect `stdout` to a file as follows:
  * `cmd > file` (overwrite or create file with result of `cmd`)
  * `cmd >> file` (append or create file with result of `cmd`)
* Redirect `stderr` to a file as follows:
  * `cmd 2> file` (overwrite or create file with error result of `cmd`)
  * `cmd 2>> file` (append or create file with error result of `cmd`)
* Redirect both `stdout` and `stderr` to a file as follows:
  * `cmd &> file` (overwrite or create file with result/error of `cmd`)
  * `cmd &>> file` (append or create file with result/error of `cmd`)
* Redirect `stdin` from a file as follows:
  * `cmd < file` (read contents of file as `stdin`)

### Background Tasks
* Any command can be run in the background by using `&` as the last argument
* Example:
  * **`input:`** `sleep 4 &`
  * **`output:`** `[processId] -> background`
* When a background process ends, `[processId] -> done` will be shown the next time the <kbd>Enter</kbd> key is pressed
