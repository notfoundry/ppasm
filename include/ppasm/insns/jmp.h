
#define ORDER_PP_DEF_0ppasm_insn_jmp_get_offset_difference \
	ORDER_PP_FN(8fn(8I, 8O, \
					8if(8greater_eq(8O, 8I), \
						0positive(8sub(8O, 8I)), \
						0negative(8sub(8I, 8O)))))


#define ORDER_PP_DEF_0ppasm_insn_jmp_generate_bytes \
	ORDER_PP_FN(8fn(8O, \
					8seq_map(\
							 8fn(8N, 8to_lit(8N)), \
							 8cond((0signed_int_sign(8O), \
									8let((8N, 0bin_2s_complement(0bin_extend(0nat_to_based(0signed_int_num(8O), 2), 32))), \
										 8seq_push_front(8nat(2,3,3), 8seq_map(0based_to_nat, 0bin_arrange_in(8, 8N))))) \
								   (8else, \
									8let((8N, 0bin_extend(0nat_to_based(0signed_int_num(8O), 2), 32)), \
										 8seq_push_front(8nat(2,3,3), 8seq_map(0based_to_nat, 0bin_arrange_in(8, 8N)))))))))

#define ORDER_PP_DEF_0ppasm_insn_jmp_to_offset \
	ORDER_PP_FN(8fn(8O, 8C, \
					0ppasm_asm_ctx_entry(8fn(8R, \
												  0ppasm_insn_jmp_generate_bytes(8O, 8R)), \
											  5)))

#define ORDER_PP_DEF_0ppasm_insn_jmp_to_label \
	ORDER_PP_FN(8fn(8L, 8C, \
					0ppasm_asm_ctx_entry( \
						8fn(8R, \
							0ppasm_insn_jmp_generate_bytes(\
								0ppasm_insn_jmp_get_offset_difference(\
									8add(5, 0ppasm_asm_ctx_get_pc(8C)),\
									0ppasm_asm_ctx_get_label_offset(8L, 8R)))), \
						5)))

#define ORDER_PP_DEF_0jmp \
	ORDER_PP_FN(8fn(8T, 8C, \
					8cond((0ppasm_is_label_reference(8T), 0ppasm_insn_jmp_to_label(8T, 8C)) \
						  (8is_num(8T), 0ppasm_insn_jmp_to_offset(0signed_int(8T, 8false), 8C)) \
						  (0is_signed_int(8T), 0ppasm_insn_jmp_to_offset(8T, 8C)) \
						  (8else, 8exit(0)))))
