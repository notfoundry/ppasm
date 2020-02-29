#include "ppasm/ppasm.h"

assemble (
    jmp (8X),
    label (8X, inc (eax)),
    nop,
    dec (rax)
)
