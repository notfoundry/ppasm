# ppasm
Are you tired of executing your C compiler on your source code to get your binaries? With `ppasm`'s **fully-preprocessor x86_64 assembler**, you can skip the compiler and move straight to the action!

Let's take a look at some of `ppasm`'s killer features:

| ppasm | literally any C compiler |
|--|--|
| 4 phases of compilation, super speedy! | 8 phases of compilation, slow and boring... |
| No types at all, maximum productivity! | Static type system, kills prototyping speed... |
| Full-blown functional language for macros! | Crappy old macro system, a complete pain... |
| Unlimited flexibility, anything is possible! | Restricted semantics, C standard controls you... |

## Table of Contents
- [Overview](#overview)
- [Tutorial](#tutorial)

## Overview
TODO: Comparison with NASM syntax

## Tutorial
Let's take a simple example of a factorial. As a C program, this might look like:
```c
unsigned int fac(unsigned int n) {
	unsigned int acc = n;
	while (--n) acc *= n;
	return acc;
}
```
and in NASM assembly, this might be represented as:
```nasm
fac:
	mov eax, edi
	mov edx, edi
	sub edx, 1
	je .end
loop:
	imul eax, edx
	sub edx, 1
	jne .loop
	ret
end:
	mov eax, 1
	ret
```
But compiling that would take significant effort! One would have to invoke the entire C compiler (a heavyweight tool!) to produce a binary from the first snippet, and one would need to get a third-party assembler to do anything useful with the second. Not so with `ppasm`:
```c
#include <ppasm/ppasm.h>

assemble (
	mov (eax, edi),
	mov (edx, edi),
	sub (edx, 1),
	je (8R),

	label (8L, imul (eax, edx)),
	sub (edx, 1),
	jne (8L),

	label (8R, mov (eax, 1)),
	ret
)
```
By simply running this through your C preprocessor, the program will be compiled into a string containing the raw-escaped bytes of the assembled instructions! To get the final binary file, all one needs to do is run `printf "%b"` on the output and redirect the resulting binary stream into your file of choice!
