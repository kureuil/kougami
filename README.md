# Kougami

A linter for C code enforcing Epitech's coding standard (also known as
"La Norme").

The parsing is done by [Clang][clang] (using `libclang`) and the program then
visits the generated tree and outputs encountered errors.

This probably should have been built using [LibTooling][libtooling] but I was
too lazy to checkout llvm and build it from source (Currently a WIP).

## Usage

```bash
$ kougami src/main.c -I ./inc/
```

## Checked rules

* a file shouldn't contain more than 5 functions
* only includes, defines, prototypes & declarations are allowed in header files
* macros defines are not allowed in source file (except feature test macros)
* variable names should only contain lower cased letters, numbers and underscores
* function names should only contain lower cased letters, numbers and underscores
* a function cannot take more than 4 parameters
* macro names should only contain upper cased letters, numbers and underscores
* structure names should be prefixed by `s_`
* typedef names should be prefixed by `t_`
* a typedef on a structure should match the structure name (`s_*` -> `t_$1`)
* union names should be prefixed by `u_`
* enum names should be prefixed by `e_`
* a function cannot take a structure by copy, always pass a pointer to the structure
* `switch` is forbidden
* `for` is forbidden
* `goto` is forbidden
* `do`...`while` is forbidden
* a function cannot have more than 25 lines between its brackets
* multiline macros are forbidden
* a control structure is always followed by a line feed (only compound statements are checked)

### Bonus rules

* includes directives shouldn't contain relative paths
* label statements are forbidden (because gotos are forbidden)

## Unchecked rules

* only one instruction per line
* header inclusion must be justified (no unused included header in a header)
* prototypes are not allowed in source file
* no comments in function bodies
* comments begin by a `/*` line, are finished by a `*/` line, and in between lines begin with `**`
* general code indentation (Emacs/Allman style)
* variables names are aligned with the enclosing function's name
* file names should only contain lower cased letters, numbers and underscores
* directory names should only contain lower cased letters, numbers and underscores
* ANSI style declaration of variable (declaration block, empty line, then instructions block)
* declaration must be aligned using tabs, function prototypes must also be aligned
* affecting a variable while declaring it is forbidden, except when the variable is declared `static` or `global`
* the pointer operator must always be written next to the variable (or function) name, never the type
* function parameters will use the ISO/ANSI syntax
* no space between a function name and its opening parenthesis
* a keyword is always followed by a space, except for sizeof
* no space after a unary operator
* all binary & ternary operators are surrounded by a single space
* nested macros must be properly indented
* functions definitions must be surrounded by an empty line
* header files must have guard to protected them against multiple inclusion
* an unused include is forbidden
* Epitech's source header at top of each file

## Uncheckable rules

Due to the current program architecture and foundations (libclang vs. LibTooling)
or due to the very nature of the rule, the following rules cannot be checked.

* 80 characters by line (this one is quite controversial)
* characters following a `#if` or a `#ifdef ` must be indented (???) (libclang does not parse whitespaces)
* commas are only allowed when separating parameters (libclang does not consider the comma a "real" operator)
* commas are followed by a space (or a line feed) (libclang does not consider the comma a "real" operator)

## Requirements

* Clang/LLVM >= 3.8

## Building

### Requirements

* CMake >= 2.8.7
* Clang/LLVM >= 3.8

```bash
$ git clone https://github.com/kureuil/kougami.git
$ cd kougami
$ mkdir build && cd $_
$ cmake ..
$ make
# Optional
$ sudo make install
```

[clang]: http://clang.llvm.org/ "Clang website"
[libtooling]: http://clang.llvm.org/docs/LibTooling.html "LibTooling documentation"
