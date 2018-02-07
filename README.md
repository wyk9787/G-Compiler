# Compiler

## Overview
This is a simple compiler written in C/C++ that will be able to compile a primitive language created in this project.

## Usage

### Option 1: Pass an input file

`./build/apps/compiler [flags] [args]`

Available flags:

*  -f --file		take one argument as the filename of the input

*	-l --length		prints the lengths of each of the arguments

*	-h --help		prints the help message

### Option 2: Use echo to input from stdin

If there is no `-f` or `--file` present in the flag list, the program will take input from stdin.

See Example section down below.

### Setup
[None]

### Building
`make all`

All the object files will store under `./build/objects`.

All the executable files will store under `./build/apps`.

### Testing
`make test`

If there is no error presents, that means all the inputs from `./test/test.in` are verified with expected output from `./test/expected.out`.

Otherwise, you can find the error in `./test/diff.txt`

### Cleaning
`make clean`

## Language Grammar
`e ::= n | (+ e1 e2) | (- e1 e2) | (* e1 e2) | (/ e1 e2)
       | true | false | (<= e1 e2) | (if e1 e2 e3)
       | f | NaN`

### Additional Rules:

1. `f` is a floating point with the form `[0-9]+.[0-9]+`

2. `if` takes three expression, the first one has to be a boolean (`true` or `false`)

3. `+`, `-`, `*`, `/`, and `<=` do not take boolean as input

4. Any arithmetic expressions including `NaN` will be evaluated to `NaN`.
   - e.g. `(+ 2 NaN)` will be evaluated to `NaN`

5. `(/ 0 0)` is also evaluated to `NaN`

## Example
`echo "(* 1 (+ (/ 4 3) (- 2 5)))" | ./build/apps/compiler`

The program will return -2


`echo "(if true (+ 2.34 3.2) (* 2 5))" | ./build/apps/compiler`

The program will return 5.540000


`./build/apps/compiler -f test/tests.in`

The program's output is saved in test/result.txt


## Author
Garrett Wang

## Acknowledgement
Peter-Michael Osera
