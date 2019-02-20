# Compiler

## Overview
G-compiler is a compiler written in C/C++ that is able to compile a OCaml-syntax-like functional programming language with state, named __G__. You can find grammar for __G__ [here](#grammar). G-compiler also supports translating the G program into intermediate C program (see [C-Translation](#c-translation) for detail).

## Supported System 

* Mac OS

* UNIX (not yet)

## Usage

```
Usage: ./build/compiler [-h|--help] [-l|--length]
                        [-f|--filename <filename>]
                        [-t|--translate <filename>]
                        [-L|--lex] [-P|--PARSE] [-p|--parse] [-s|--step]
NOTE:[-f|--filename <filename>] has to present to take the input file


Available flags:

* -f --file <filename>  take one argument as the filename of the input

* -t --translate <filename>  translate the original program into a C program, saved in file <filename>

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

## C-Translation

With the flag `-t <filename>`, G-compiler is able to translate the G program into a C program. Now it supports translating binary operations, if expressions, let bindings and functional applications into a C program. You can then use either `gcc` or `clang` to compile the C program as normal. See [Example](#example) sections for more info.

More translating features are still under development.

## Example

See directory `./test` for examples.

* `./test/exp_test` are examples(tests) for G program
* `./test/type_test` are examples(tests) for checking type errors in G program
* `./test/translate_test` are examples(tests) for translating G programs into C programs

## Language

### Grammar

```
#include <filename>

prog:
  decllist eof                  

formal:
  var : typ                 

formallist:
  formal    
| formallist , formal    

decl:
  let var ( formallist ) : typ = exp ;;

decllist:
  decl
| decllist decl

exp:
  exp_app             

exp_app:
  var expslist    
| exp_ops                        

expslist:
  exp_ops       
| expslist exp_ops     

exp_ops:
  exp_ops + exp_ops             
| exp_ops - exp_ops             
| exp_ops * exp_ops             
| exp_ops / exp_ops             
| exp_ops <= exp_ops            
| exp_ops < exp_ops             
| exp_ops == exp_ops            
| exp_ops > exp_ops             
| exp_ops >= exp_ops            
| ( exp_ops , exp_ops )     
| fst ( exp_ops )           
| snd ( exp_ops )           
| car ( exp_ops )           
| cdr ( exp_ops )           
| empty ( exp_ops )         
| exp_ops :: exp_ops            
| { } : typ                 
| ref ( exp_ops )           
| ! ( exp_ops )             
| exp_ops := exp_ops            
| exp_ops ; exp_ops             
| ( exp_ops ) %prec ->    
| typ var = { exp_ops }   
| struct { struct_statement_list }
| exp_ops  . var              
| exp_base                        

exp_base:
  ( )                         
| int                           
| double                        
| true                          
| false                         
| NaN                           
| var                           
| if exp then exp else exp
| let var : typ  = exp in exp
| while exp do exp end
| ( exp )                   

struct_statement_list: struct_statement
| struct_statement_list struct_statement

struct_statement:
  typ var => exp     

typ:
  int                          
| float                        
| bool                         
| unit                         
| struct                       
| typ -> typ                    
| typ * typ         
| { typ }                    
| < typ >                     
| ( typ )                     
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

## Muse

> When it’s 3 A.M., and you’ve been debugging for 12 hours, and you encounter a virtual static friend protected volatile templated function pointer, you want to go into hibernation and awake as a werewolf and then find the people who wrote the C++ standard and bring ruin to the things that they love. The C++ STL, with its dyslexia-inducing syntax blizzard of colons and angle brackets, guarantees that if you try to declare any reasonable data structure, your first seven attempts will result in compiler errors of Wagnerian fierceness:

>
``` C++
Syntax error: unmatched thing in thing from std::nonstd::__ map<_Cyrillic, _$$$dollars>const basic_string< epic_ mystery,mongoose_traits &lt; char>, __default_alloc_<casual_ Fridays = maybe>>
```

From James Mickens' [_The Night Watch_](https://www.usenix.org/system/files/1311_05-08_mickens.pdf)

## Author
Garrett Wang

## Acknowledgement
Peter-Michael Osera
