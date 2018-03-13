# Compiler

## Overview
This is a simple compiler written in C/C++ that will be able to compile a primitive language created in this project.

## Usage

```
Usage: ./build/compiler [-h|--help] [-l|--length]
                        [-f|--filename <filename>] [-L|--lex] [-P|--PARSE] [-p|--parse] [-s|--step]
NOTE:[-f|--filename <filename>] has to present to take the input file


Available flags:

* -f --file   take one argument as the filename of the input

* -p --parse   generate the abstract syntax tree from parsing

  - This is the only option that will stop the compiler from interpreting the output

* -P --PARSE   generate EXTREMELY verbose parsing stages (Debug use only)

* -L --lex   generate the tokens and matching rules in .l file

* -l --length   prints the lengths of each of the arguments

* -s --step   prints the intermediate step of each evaluation

* -h --help   prints the help message

```

### Setup

You need to install both bison (version >= 3.0.4) and flex (version >= 2.6.4).

* Bison: `brew install bison`
* Flex: `brew install flex`

### Building
`make all`

### Testing
`make test`

If there are errors present, you can find the error in `./test/diff.txt`

### Cleaning
`make clean`

## Language

### Grammar

```
#include <filename>

e ::= n | (e) | e1 + e2 | e1 - e2 | e1 * e2 | e1 / e2
        | true | false | f | NaN | x
        | e1 <= e2 | e1 < e2 | e1 == e2 | e1 > e2 | e1 >= e2
        | if (e1) {e2} else {e3}
        | let [x:t] = e1 in e2
        | fun [x:t1] : t2 -> e | rec f [x:t1] : t2 -> e | e1 (e2)
        | () | (e1, e2) | fst (e) | snd (e)
        | [] : t | e1 :: e2 | car (e) | cdr (e) | empty? (e)
        | ref (e) | e1 := e2 | !(e) | e1; e2
        | while (e1) {e2}
        | x = {e}
        | struct { struct_statement_list }
        | e.x

t ::= int | float | bool | [-] | t1 -> t2 | t1 * t2 | unit | {t} | <t>

struct_statement_list ::= struct_statement
                        | struct_statement_list struct_statement

struct_statement ::= t x => e,

```

### Precedence

```

1. ( )  left associative

2. . left associative

3. * / left associative

4. + - left associative

5. <= < > >= == left associative

6. -> :: right associative

7. if then else

8. := left associative

9. ; left associative

10. ! ref right associative

```

## Example

See directory `./test` for examples.

## Author
Garrett Wang

## Acknowledgement
Peter-Michael Osera
