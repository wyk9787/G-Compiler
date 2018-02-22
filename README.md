# Compiler

## Overview
This is a simple compiler written in C/C++ that will be able to compile a primitive language created in this project.

## Usage

```
Usage: ./build/compiler [-h|--help] [-l|--length] [-f|--filename <filename>] [-L|--lex] [-P|--PARSE] [-p|--parse]
NOTE:[-f|--filename <filename>] has to present to take the input file
```

Available flags:

* -f --file   take one argument as the filename of the input

* -p --parse   generate the abstract syntax tree from parsing

  - This is the only option that will stops the compiler from interpreting the output

* -P --PARSE   generate EXTREMELY verbose parsing stages (Debug use only)

* -L --lex   generate the tokens and matching rules in .l file

* -l --length   prints the lengths of each of the arguments

* -h --help   prints the help message

### Setup

You need to install both bison (version >= 3.0.4) and flex (version >= 2.6.4).

* Bison: `brew install bison`
* Flex: `brew install flex`

### Building
`make all`

### Testing
`make test`

If there is no error presents, that means all the inputs from `./test/test.in` are verified with expected output from `./test/expected.out`.

Otherwise, you can find the error in `./test/diff.txt`

### Cleaning
`make clean`

## Language

### Grammar

```
e ::= n | (e) | e1 + e2 | e1 - e2 | e1 / e2
        | true | false | e1 <= e2 | if e1 then e2 else e3
        | f | NaN
```

### Precedence

1. * /

2. + -

3. <=

### Additional Rules: (Since there is no type system yet)

1. `f` is a floating point with the form `[0-9]+.[0-9]+`

2. `if` takes three expression, the first one has to be a boolean (`true` or `false`)

3. `+`, `-`, `*`, `/`, and `<=` do not take boolean as input

4. Any arithmetic expressions including `NaN` will be evaluated to `NaN`.
   - e.g. `NaN + 2` will be evaluated to `NaN`

5. `0 / 0` is also evaluated to `NaN`

## Example

`./build/compiler -f ./test/test1.scr`

The program will return `NaN`

`./build/compiler -f ./test/test1.scr -p`

The program will return `(if (if false (+ 1 3) false) (+ 10.230000 0.770000) (if false (+ 3 (/ 2.500000 2)) (/ 0 0)))`

## Author
Garrett Wang

## Acknowledgement
Peter-Michael Osera
