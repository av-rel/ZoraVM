# ZoraVM ( Zora Virtual Machine )

# Description
## ZoraVM is a virtual machine written for Zora Programming Language using its own assembly code for cross-platform compatibility.
## This is rather incomplete.


# Features
- [x] Assembly
- [x] Cross-platform
- [] C Wrapper
- [] Compiler

# How will it work?
## ZVM will be able to run Zora Assembly Code.
## This will be compiled via GCC and TCC for Bytecode.
## It will just use C as a wrapper to make a inbuilt runtime for Zora like the hardcoded code will just have change in instructions of array which will be executing the code.
## It will be able to run on any platform which supports C.
## It will be used to make a compiler for its own high level language.

### Zora Assembly Code is a assembly language for ZoraVM. It is a stack based and low level language.

# Examples 
[Hello, world](./examples/hw.zsm)
```zorasm
; This will print `Hello, world`

#main
	!push "Hello, world\n"			 ; push to the stack
	!print							 ; Print the top of the mem stack
	!halt 0							 ; exit with status code 0
```
