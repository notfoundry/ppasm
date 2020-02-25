
#define inc(reg) 8ppasm_insn_inc(8quote(reg))

#define push(reg) 8ppasm_insn_push(8quote(reg))

#define mov(a, b) 8ppasm_insn_mov(8quote(a), 8quote(b))

#define pop(reg) 8ppasm_insn_pop(8quote(reg))

#define ret 8ppasm_insn_ret(8nil)


#define dword(...) 8ppasm_indop_parse(8((__VA_ARGS__)))


#define label(l, insn) 8ppasm_intrinsic_label(8quote(l), insn)

#define define(name, var) 8ppasm_intrinsic_define(8quote(name), var)

#define section(name, ...) 8ppasm_intrinsic_section(8quote(name), 8quote((__VA_ARGS__)))


#define macro_apply(insn, ...) 8eval(8env_nil, 8adjacent(8(insn), 8tuple(__VA_ARGS__)))