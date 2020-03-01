

#define PPASM_INSN_MOV_MEM_PREFIX_32_0_32_0 (103)
#define PPASM_INSN_MOV_MEM_PREFIX_32_0_32_1 (103)(65)
#define PPASM_INSN_MOV_MEM_PREFIX_32_0_64_0 
#define PPASM_INSN_MOV_MEM_PREFIX_32_0_64_1 (65)
#define PPASM_INSN_MOV_MEM_PREFIX_32_1_32_0 (103)(68)
#define PPASM_INSN_MOV_MEM_PREFIX_32_1_32_1 (103)(69)
#define PPASM_INSN_MOV_MEM_PREFIX_32_1_64_0 (68)
#define PPASM_INSN_MOV_MEM_PREFIX_32_1_64_1 (69)
#define PPASM_INSN_MOV_MEM_PREFIX_64_0_32_0 (103)(72)
#define PPASM_INSN_MOV_MEM_PREFIX_64_0_32_1 (103)(73)
#define PPASM_INSN_MOV_MEM_PREFIX_64_0_64_0 (72)
#define PPASM_INSN_MOV_MEM_PREFIX_64_0_64_1 (73)
#define PPASM_INSN_MOV_MEM_PREFIX_64_1_32_0 (103)(76)
#define PPASM_INSN_MOV_MEM_PREFIX_64_1_32_1 (103)(77)
#define PPASM_INSN_MOV_MEM_PREFIX_64_1_64_0 (76)
#define PPASM_INSN_MOV_MEM_PREFIX_64_1_64_1 (77)

#define ORDER_PP_DEF_0ppasm_insn_mov_mem_prefix \
	ORDER_PP_FN(8fn(8L, 8R, \
					8let((8A, 8cat(8(PPASM_REGISTER_SIZE_), 8L)) \
                         (8B, 8cat(8(PPASM_REGISTER_SIZE_), 8R)) \
					   	 (8E, 8cat(8(PPASM_REGISTER_BLOCK_), 8L)) \
                         (8F, 8cat(8(PPASM_REGISTER_BLOCK_), 8R)), \
				  	     8let((8P, 8cat(8(PPASM_INSN_MOV_MEM_PREFIX_), 8A, 8(_), 8E, 8(_), 8B, 8(_), 8F)), \
                              8P))))

#define ORDER_PP_DEF_0ppasm_insn_mov_reg_to_reg \
    ORDER_PP_FN(8fn(8A, 8B, 8C, ))

#define ORDER_PP_DEF_0ppasm_insn_mov_mem_to_reg \
    ORDER_PP_FN(8fn(8A, 8B, 8C, ))

#define ORDER_PP_DEF_0ppasm_insn_mov_reg_to_mem \
    ORDER_PP_FN(8fn(8A, 8B, 8C, ))

#define ORDER_PP_DEF_0ppasm_insn_mov_const_to_reg \
    ORDER_PP_FN(8fn(8A, 8B, 8C, ))

#define ORDER_PP_DEF_0ppasm_insn_mov_const_to_mem \
    ORDER_PP_FN(8fn(8A, 8B, 8C, ))



#define ORDER_PP_DEF_0mov \
  ORDER_PP_FN(8fn(8A, 8B, 8C, \
				  8cond( \
						(8and(0ppasm_is_register(8A), 0ppasm_is_register(8B)), 0ppasm_insn_mov_reg_to_reg(8A, 8B, 8C)) \
						(8and(0ppasm_is_register(8A), 0ppasm_is_indop(8B)), 0ppasm_insn_mov_mem_to_reg(8A, 8B, 8C)) \
						(8and(0ppasm_is_indop(8A), 0ppasm_is_register(8B)), 0ppasm_insn_mov_reg_to_mem(8A, 8B, 8C)) \
						(8and(0ppasm_is_register(8A), 8is_num(8B)), 0ppasm_insn_mov_const_to_reg(8A, 8B, 8C)) \
						(8and(0ppasm_is_indop(8A), 8is_num(8B)), 0ppasm_insn_mov_const_to_mem(8A, 8B, 8C)) \
						(8else, 8exit(0)))))
