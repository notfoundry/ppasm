#define inc(reg) 0inc(8(reg))

#define push(reg) 0push(8(reg))

#define mov(a, b) 0mov(8(a), 8(b))

#define pop(reg) 0pop(8(reg))

#define ret 0ret(8nil)

#define jmp(target) 0jmp(8(target))


#define byte(...) ORDER_PP(0byte(8((__VA_ARGS__))))

#define word(...) ORDER_PP(0word(8((__VA_ARGS__))))

#define dword(...) ORDER_PP(0dword(8((__VA_ARGS__))))

#define qword(...) ORDER_PP(0qword(8((__VA_ARGS__))))


#define negative(...) \
    ORDER_PP(0negative( \
                         8let((8X, 8((__VA_ARGS__))), \
                              8if(8and(8is_tuple(8X), 8greater(8tuple_size(8X), 1)), \
                                  8seq_of_digits_to_nat(8tuple_to_seq(8X)), \
                                  8lit_to_nat(__VA_ARGS__))) \
                         ))

#define positive(...) \
    ORDER_PP(0positive( \
                         8let((8X, 8((__VA_ARGS__))), \
                              8if(8and(8is_tuple(8X), 8greater(8tuple_size(8X), 1)), \
                                  8seq_of_digits_to_nat(8tuple_to_seq(8X)), \
                                  8lit_to_nat(__VA_ARGS__))) \
                         ))


#define label(l, insn) 0label(8(l), insn)

#define section(name, ...) 0section(8(name), 8((__VA_ARGS__)))