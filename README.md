# Compiler

## Overview
G-compiler is a simple toy compiler written in C/C++ that is able to compile a OCaml-syntax-like programming language. You can find grammar for this language [here](#grammar). G-compiler is able to compile the program into intermediate C program and then compile down to web assembly.

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
// | ( exp_ops ) %prec ->    
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

## Example

See directory `./test` for examples.

## Author
Garrett Wang

## Acknowledgement
Peter-Michael Osera
