#Author: Timothy Schultz
#Project 4 main.cpp scanner.cpp parser.cpp generator.cpp scanner.h token.h parser.h generator.h generator.h

Storage = Local

Test Programs:

Success
1. p4g1.txt
2. p4g2.txt
3. p4g3.txt
4. p4g4.txt

Error
1. p4g5.txt 
(Identifier error found on line: 2.)
(Identifier x was declaredon line: 1.)
2. p4g6.txt
(Identifier y was not declared.)
3. p4g7.txt
(Identifier x was not declared.)
4. p4g8.txt
(Error Void Identifier was not found to create label to branch to.)
(Deleting file p4g8.asm)
5. p4g9.txt
(Error label already created)
(Deleting file p4g9.asm)

The program is to parse the input, generate a parse tree, perform static semantics, and then generate a 
target file containing target(assembly) code. The focus of P4 is to test target code and storage allocation.
Testing will be performed by running the generated targets to assess if the runtime behavior is correct.

Target Name:
kb.asm if keyboard input
file.asm if file was the input. The base name matches that of the input file.

Program:
1. Code generation
2. Storage allocation local - Matches local option in P3. Variables are considered global in P3 are scoped 
in the entire program and variables in a block are scoped in that block as in P3.

## Installation

The main, scanner, parser, and generator has been tested on CentOS v7 with gcc v4.8.5.

Using Makefile.

```
make
```

## Usage

compfs [-h]
compfs [file]
compfs < [file] 

-h		Displays usage message.
[file]		Any file containing strings.

* < redirects file and reads strings as keyboard input.

```
./compfs [option var]
```

## Output

Terminal:

Displays the name of the target file generated.

Files:

[Input File Name].asm
kb.asm

New Error Message:

Error Void Identifier was not found to create label to branch to.
Deleting file ***.asm

Error label already created.
Deleting file ***.asm

## Comments

