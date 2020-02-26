#define inc(reg) 0inc(8(reg))

#define push(reg) 0push(8(reg))

#define mov(a, b) 0mov(8(a), 8(b))

#define pop(reg) 0pop(8(reg))

#define ret 0ret(8nil)


#define byte(...) ORDER_PP(0byte(8((__VA_ARGS__))))

#define word(...) ORDER_PP(0word(8((__VA_ARGS__))))

#define dword(...) ORDER_PP(0dword(8((__VA_ARGS__))))

#define qword(...) ORDER_PP(0qword(8((__VA_ARGS__))))


#define label(l, insn) 0label(l, insn)

#define section(name, ...) 0section(8(name), 8((__VA_ARGS__)))