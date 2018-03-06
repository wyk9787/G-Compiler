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
e ::= n | (e) | e1 + e2 | e1 - e2 | e1 * e2 | e1 / e2
        | true | false | f | NaN | x
        | e1 <= e2 | e1 < e2 | e1 == e2 | e1 > e2 | e1 >= e2
        | if e1 then e2 else e3
        | let [x:t] = e1 in e2
        | fun [x:t1] : t2 -> e | rec f [x:t1] : t2 -> e | e1 (e2)
        | () | (e1, e2) | fst (e) | snd (e)
        | [] : t | e1 :: e2 | car (e) | cdr (e) | empty? (e)

t ::= int | float | bool | t1 -> t2 | t1 * t2 | {t}
```

### Precedence

```
1. ( )  left associative

2. * / left associative

3. + - left associative

4. <= < > >= == left associative

5. -> :: right associative

6. if then else

```

### Additional Rules: (Since there is no type system yet)

1. `f` is a floating point with the form `[0-9]+.[0-9]+`

2. `if` takes three expression, the first one has to be a boolean (`true` or `false`)

3. `+`, `-`, `*`, `/`, `<=`, `<`, `==`, `>`, and `>=` do not take boolean as input

4. Any arithmetic expressions including `NaN` will be evaluated to `NaN`.
   - e.g. `NaN + 2` will be evaluated to `NaN`

5. `0 / 0` is also evaluated to `NaN`

## Example

`./build/compiler -f ./test/test1.src`

The program will return `NaN`

`./build/compiler -f ./test/test1.src -p`

The program will return

```
(if (if false then (1 + 3) else false) then (10.230000 + 0.770000) else (if false then (3 + (2.500000 / 2)) else (0 / 0)))
```

`./build/compiler -f ./test/test1.src -s`

The program will return

```
(if (if false then (1 + 3) else false) then (10.230000 + 0.770000) else (if false then (3 + (2.500000 / 2)) else (0 / 0)))
(if false then (10.230000 + 0.770000) else (if false then (3 + (2.500000 / 2)) else (0 / 0)))
(if false then (3 + (2.500000 / 2)) else (0 / 0))
(0 / 0)
NaN
```

## Author
Garrett Wang

## Acknowledgement
Peter-Michael Osera
