# asc
An interpreter for my scripting language, *asc.*

## Installation
================================================================================
1. Run `make` to build the interpreter, `make static` to build a statically
   linked library, or `make dynamic` to build a dynamically linked one.
2. Run `make install` to move the library to /usr/lib or the interpreter to
   /usr/bin.
3. Run `make clean` to clear the build directory and delete the temporary
   library files

## Use
================================================================================
### Library
* All headers are in the sub-folder *asc,* and must be included with `<asc/[file].h>`.
* Add `-lasc` to your linker or compiler switches.

### Interpreter
* Run `asc` to launch an interactive interpreter.
* Run `asc [options]` to launch an interpreter with the specified options.
Option | Result
---------------
`-c command` | Run `command`. Only one command can be specified per `-c` switch. Commands are executed in the order specified.
`-s script` | Run `script`. If `script` is not in the current working directory, path must be prepended. If no extension is specified, `.asc` will be assumed. Only one script can be specified per `-s` switch. Scripts are executed in the order specified.
`-x` | After all commands and/or scripts have finished, return to an interactive interpreter. Multiple `-x` switches will not change the behavior.
`-i file` | Redirect the input stream to a text file.
`-o file` | Redirect the output stream to a text file.
`-e file` | Redirect the error stream to a text file.

## Removal
================================================================================
Run `make remove` to remove the interpreter and library.
