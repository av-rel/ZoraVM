# Unfinished Project -- Anything can change at any time
# ZoraVM ( Zora Virtual Machine )

# Description
## ZVM is a virtual machine written for Zora Programming Language using its own assembly code for cross-platform compatibility.

#TODO
# Features
- [] Assembly
- [] Cross-platform
- [] C Wrapper
- [] Compiler

# How will it work?
## ZVM will be able to run Zora Assembly Code.
## This will be compiled via GCC, Clang, or TCC for Bytecode.
## It will just use C as a wrapper to make a inbuilt runtime for Zora like the hardcoded code will just have change in instructions of array which will be executing the code.
## It will be able to run on any platform which supports C.
## It will be used to make a compiler for its own high level language.

## Example
---
### Print sizeof string
* Print `Hello, world\n`
```c
/*include and declaration*/

	Program program[] = {
    	PushStr("hello, world\n"), //pushes to the mem stack
    	Print(),					// print the top of the stack (i.e string)
    	Halt(0),					// exit with status code 0
  	};
  
	ZoraVM(program, sizeof(program)/sizeof(program[0])); //pass params

/*rest code */
```
---
* Loop
```
	Program program[] = {
		PushInt(33),				// push 33 to mem stack
		Store(0),					// store it to the block or global stack at addr 0 `int x = 33;`
		Load(0),					// load from the global stack from addr 0
		Dec(),						// decrement the number `x--`
		Store(0),					// update the value at addr 0 `x = 32;`
		Load(0),
    	Print(),					// print it to the terminal `32`
    	PushStr("\n"),				// push newline string
    	Print(),					// print newline
		Load(0),					// load from addr 0
		PushInt(10),				// push `10` to the mem stack
		CmpGt(),					// cmp the top of two stack i.e `x > 10;`
		JmpIf(2),					// jmp to the the (2 + 1) program
    	PushStr("Loop end!\n"),		// push to the mem stack		//will run after execution
    	Print(),					// print
    	Halt(0),				    	// exit with status code 0
	};

	//will print till x (32) > 10;

	ZoraVM(program, sizeof(program)/sizeof(program[0])); //pass params

```
