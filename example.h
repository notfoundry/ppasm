#include "ppasm/ppasm.h"

assemble (
    mov (eax, dword (rbp, (eax, 4))),
    inc (rax)
)