#include "order/interpreter.h"

#include "arithmatic/signed.h"
#include "arithmatic/based_int.h"
#include "arithmatic/binary.h"

#include "byte_escapes.h"
#include "indirect_operand.h"
#include "keywords.h"
#include "typing.h"
#include "util.h"
#include "x86_register_syms.h"


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


#define ORDER_PP_DEF_0ppasm_insn_inc_generate_bytes_and_size \
	ORDER_PP_FN(8fn(8R, 8C, \
					8let((8S, 8cat(8(PPASM_REGISTER_SIZE_), 8R)) \
					   	 (8I, 8cat(8(PPASM_REGISTER_INDEX_), 8R)) \
					   	 (8B, 8cat(8(PPASM_REGISTER_BLOCK_), 8R)), \
				  	8cond( \
						  (8and(8equal(8S, 64), 8equal(8B, 0)), \
						   8pair(8seq(8to_lit(8nat(7,2)), 8to_lit(8nat(2,5,5)), 8to_lit(8add(8nat(1,9,2), 8I))), 3)) \
						  (8and(8equal(8S, 32), 8equal(8B, 0)), \
						   8pair(8seq(8to_lit(8nat(2,5,5)), 8to_lit(8add(8nat(1,9,2), 8I))), 2)) \
						  (8and(8equal(8S, 64), 8equal(8B, 1)), \
						   8pair(8seq(8to_lit(8nat(7,3)), 8to_lit(8nat(2,5,5)), 8to_lit(8add(8nat(1,9,2), 8I))), 3)) \
						  (8and(8equal(8S, 32), 8equal(8B, 1)), \
						   8pair(8seq(8to_lit(8nat(6,5)), 8to_lit(8nat(2,5,5)), 8to_lit(8add(8nat(1,9,2), 8I))), 3)) \
						  (8else, 8exit(0))))))

#define ORDER_PP_DEF_0inc \
  ORDER_PP_FN(8fn(8R, 8C,			\
				  8let((8D, 0ppasm_insn_inc_generate_bytes_and_size(8R, 8C)), \
					   0ppasm_asm_ctx_entry(8fn(8R, 8tuple_at_0(8D)), 8tuple_at_1(8D)))))
  
  
  #define ORDER_PP_DEF_0ppasm_insn_dec_generate_bytes_and_size \
	ORDER_PP_FN(8fn(8R, 8C, \
					8let((8S, 8cat(8(PPASM_REGISTER_SIZE_), 8R)) \
					   	 (8I, 8cat(8(PPASM_REGISTER_INDEX_), 8R)) \
					   	 (8B, 8cat(8(PPASM_REGISTER_BLOCK_), 8R)), \
				  	8cond( \
						  (8and(8equal(8S, 64), 8equal(8B, 0)), \
						   8pair(8seq(8to_lit(8nat(7,2)), 8to_lit(8nat(2,5,5)), 8to_lit(8add(8nat(2,0,0), 8I))), 3)) \
						  (8and(8equal(8S, 32), 8equal(8B, 0)), \
						   8pair(8seq(8to_lit(8nat(2,5,5)), 8to_lit(8add(8nat(2,0,0), 8I))), 2)) \
						  (8and(8equal(8S, 64), 8equal(8B, 1)), \
						   8pair(8seq(8to_lit(8nat(7,3)), 8to_lit(8nat(2,5,5)), 8to_lit(8add(8nat(2,0,0), 8I))), 3)) \
						  (8and(8equal(8S, 32), 8equal(8B, 1)), \
						   8pair(8seq(8to_lit(8nat(6,5)), 8to_lit(8nat(2,5,5)), 8to_lit(8add(8nat(2,0,0), 8I))), 3)) \
						  (8else, 8exit(0))))))

#define ORDER_PP_DEF_0dec \
  ORDER_PP_FN(8fn(8R, 8C,			\
				  8let((8D, 0ppasm_insn_dec_generate_bytes_and_size(8R, 8C)), \
					   0ppasm_asm_ctx_entry(8fn(8R, 8tuple_at_0(8D)), 8tuple_at_1(8D)))))


#define ORDER_PP_DEF_0push \
  ORDER_PP_FN(8fn(8R, 8C,			\
		  8seq(8R)))

#define ORDER_PP_DEF_0pop \
  ORDER_PP_FN(8fn(8R, 8C,			\
		  8seq(8to_lit(8nat(1, 0)))))

#define ORDER_PP_DEF_0mov \
  ORDER_PP_FN(8fn(8A, 8B, 8C, \
				  8cond( \
						(8and(0ppasm_is_register(8A), 0ppasm_is_register(8B)), 8seq(8(reg to reg))) \
						(8and(0ppasm_is_register(8A), 0ppasm_is_indop(8B)), 8seq(8(mem to reg))) \
						(8and(0ppasm_is_indop(8A), 0ppasm_is_register(8B)), 8seq(8(reg to mem))) \
						(8and(0ppasm_is_register(8A), 8is_num(8B)), 8seq(8(const to reg))) \
						(8and(0ppasm_is_indop(8A), 8is_num(8B)), 8seq(8(const to mem))) \
						(8else, 8exit(0)))))

#define ORDER_PP_DEF_0ret \
  ORDER_PP_FN(8fn(8X, 8C, 				\
		  8seq(8to_lit(8nat(1, 9, 5)))))


#define ORDER_PP_DEF_0nop \
	ORDER_PP_FN(8fn(8X, 8C, \
					0ppasm_asm_ctx_entry(8fn(8R, 8seq(8to_lit(8nat(1,4,4)))), 1)))


#define ORDER_PP_DEF_0label \
  ORDER_PP_FN(8fn(8L, 8I, 8C, 				\
				  0ppasm_asm_ctx_entry_set_label(8L, 8ap(8I, 8C))))

#define ORDER_PP_DEF_0ppasm_is_label_reference \
	ORDER_PP_FN(8fn(8T, 8is_sym(8T)))



#define ORDER_PP_DEF_0ppasm_asm_ctx_nil ORDER_PP_CONST(()()(0))

#define ORDER_PP_DEF_0ppasm_asm_ctx_entries_key ORDER_PP_CONST(0)

#define ORDER_PP_DEF_0ppasm_asm_ctx_labels_key ORDER_PP_CONST(1)

#define ORDER_PP_DEF_0ppasm_asm_ctx_pc_key ORDER_PP_CONST(2)


#define ORDER_PP_DEF_0ppasm_asm_ctx_get_entries \
	ORDER_PP_FN(8fn(8C, 8seq_at(0ppasm_asm_ctx_entries_key, 8C)))

#define ORDER_PP_DEF_0ppasm_asm_ctx_set_entries \
	ORDER_PP_FN(8fn(8E, 8C, 8seq_set(0ppasm_asm_ctx_entries_key, 8C, 8E)))


#define ORDER_PP_DEF_0ppasm_asm_ctx_add_entry \
	ORDER_PP_FN(8fn(8E, 8C, \
					8let((8L, 0ppasm_asm_ctx_get_entries(8C)), \
						 8let((8U, 0ppasm_asm_ctx_inc_pc(\
														 0ppasm_asm_ctx_entry_get_byte_length(8E), \
														 0ppasm_asm_ctx_set_entries(8seq_push_back(8E, 8L), 8C))), \
							  8cond((0ppasm_asm_ctx_entry_has_label(8E), \
									 0ppasm_asm_ctx_add_label( \
															  0ppasm_asm_ctx_entry_get_label(8E), \
															  0ppasm_asm_ctx_get_pc(8C), \
															  8U)) \
									(8else, 8U))))))


#define ORDER_PP_DEF_0ppasm_asm_ctx_get_labels \
	ORDER_PP_FN(8fn(8C, 8seq_at(0ppasm_asm_ctx_labels_key, 8C)))

#define ORDER_PP_DEF_0ppasm_asm_ctx_set_labels \
	ORDER_PP_FN(8fn(8I, 8C, 8seq_set(0ppasm_asm_ctx_labels_key, 8C, 8I)))

#define ORDER_PP_DEF_0ppasm_asm_ctx_add_label \
	ORDER_PP_FN(8fn(8I, 8O, 8C, \
					8let((8L, 0ppasm_asm_ctx_get_labels(8C)), \
						 0ppasm_asm_ctx_set_labels(8seq_push_back(8pair(8I, 8O), 8L), 8C))))

#define ORDER_PP_DEF_0ppasm_asm_ctx_get_label_offset \
	ORDER_PP_FN(8fn(8I, 8C, \
					8let((8L, 0ppasm_asm_ctx_get_labels(8C)), \
						 8tuple_at_1(8seq_head(8seq_filter(8fn(8X, \
												   8same(8tuple_at_0(8X), 8I)), \
											   8L))))))


#define ORDER_PP_DEF_0ppasm_asm_ctx_get_pc \
	ORDER_PP_FN(8fn(8C, 8seq_at(0ppasm_asm_ctx_pc_key, 8C)))

#define ORDER_PP_DEF_0ppasm_asm_ctx_set_pc \
	ORDER_PP_FN(8fn(8E, 8C, 8seq_set(0ppasm_asm_ctx_pc_key, 8C, 8E)))

#define ORDER_PP_DEF_0ppasm_asm_ctx_inc_pc \
	ORDER_PP_FN(8fn(8N, 8C, \
					8let((8L, 0ppasm_asm_ctx_get_pc(8C)), \
						 0ppasm_asm_ctx_set_pc(8add(8N, 8L), 8C))))



#define ORDER_PP_DEF_0ppasm_asm_ctx_entry_nil() ORDER_PP_MACRO(8env_nil)

#define ORDER_PP_DEF_0ppasm_asm_ctx_entry_code_gen_key ORDER_PP_CONST(8G)

#define ORDER_PP_DEF_0ppasm_asm_ctx_entry_byte_length_key ORDER_PP_CONST(8B)

#define ORDER_PP_DEF_0ppasm_asm_ctx_entry_label_key ORDER_PP_CONST(8L)


#define ORDER_PP_DEF_0ppasm_asm_ctx_entry_get              \
  ORDER_PP_FN(8fn(8S, 8C, 8env_ref(8S, 8C)))

#define ORDER_PP_DEF_0ppasm_asm_ctx_entry_set		\
  ORDER_PP_FN(8fn(8S, 8C, 8X, 8env_bind(8S, 8C, 8X)))

#define ORDER_PP_DEF_0ppasm_asm_ctx_entry_has		\
  ORDER_PP_FN(8fn(8S, 8C, 8env_has(8S, 8C)))


#define ORDER_PP_DEF_0ppasm_asm_ctx_entry_get_code_gen \
	ORDER_PP_FN(8fn(8E, 0ppasm_asm_ctx_entry_get(0ppasm_asm_ctx_entry_code_gen_key, 8E)))

#define ORDER_PP_DEF_0ppasm_asm_ctx_entry_set_code_gen \
	ORDER_PP_FN(8fn(8G, 8E, 0ppasm_asm_ctx_entry_set(0ppasm_asm_ctx_entry_code_gen_key, 8E, 8G)))

#define ORDER_PP_DEF_0ppasm_asm_ctx_entry_has_code_gen \
	ORDER_PP_FN(8fn(8E, 0ppasm_asm_ctx_entry_has(0ppasm_asm_ctx_entry_code_gen_key, 8E)))


#define ORDER_PP_DEF_0ppasm_asm_ctx_entry_get_byte_length \
	ORDER_PP_FN(8fn(8E, 0ppasm_asm_ctx_entry_get(0ppasm_asm_ctx_entry_byte_length_key, 8E)))

#define ORDER_PP_DEF_0ppasm_asm_ctx_entry_set_byte_length \
	ORDER_PP_FN(8fn(8B, 8E, 0ppasm_asm_ctx_entry_set(0ppasm_asm_ctx_entry_byte_length_key, 8E, 8B)))

#define ORDER_PP_DEF_0ppasm_asm_ctx_entry_has_byte_length \
	ORDER_PP_FN(8fn(8E, 0ppasm_asm_ctx_entry_has(0ppasm_asm_ctx_entry_byte_length_key, 8E)))


#define ORDER_PP_DEF_0ppasm_asm_ctx_entry_get_label \
	ORDER_PP_FN(8fn(8E, 0ppasm_asm_ctx_entry_get(0ppasm_asm_ctx_entry_label_key, 8E)))

#define ORDER_PP_DEF_0ppasm_asm_ctx_entry_set_label \
	ORDER_PP_FN(8fn(8L, 8E, 0ppasm_asm_ctx_entry_set(0ppasm_asm_ctx_entry_label_key, 8E, 8L)))

#define ORDER_PP_DEF_0ppasm_asm_ctx_entry_has_label \
	ORDER_PP_FN(8fn(8E, 0ppasm_asm_ctx_entry_has(0ppasm_asm_ctx_entry_label_key, 8E)))


#define ORDER_PP_DEF_0ppasm_asm_ctx_entry \
	ORDER_PP_FN(8fn(8G, 8S, \
					0ppasm_asm_ctx_entry_set_code_gen(8G, \
					0ppasm_asm_ctx_entry_set_byte_length(8S, \
					0ppasm_asm_ctx_entry_nil()))))






#define ORDER_PP_DEF_0ppasm_eval \
  ORDER_PP_FN(8fn(8F, 8eval(8env_nil, 8F)))

#define ORDER_PP_DEF_0ppasm_process_insn \
  ORDER_PP_FN(8fn(8O, 8C, \
				  0ppasm_asm_ctx_add_entry(8ap(0ppasm_eval(8O), 8C), 8C)))

#define ORDER_PP_DEF_0ppasm_expand_macro \
  ORDER_PP_FN(8fn(8M, 8C, \
		  8let((8R, 0ppasm_eval(8M)), \
		  	   8cond((8is_fn(8R), 0ppasm_asm_ctx_add_entry(8ap(8R, 8C), 8C)) \
				 	 (8else, 8seq_fold(8fn(8A, 8O, 0ppasm_asm_ctx_add_entry(8ap(8O, 8C), 8A)),	\
										8C,					\
										8cond(\
											(8is_tuple(8R), 8tuple_to_seq(8R)) \
											(8is_seq(8R), 8R) \
											(8else, 8exit(0)))))) \
									)))

#define ORDER_PP_DEF_0ppasm_expand_macro_seq \
  ORDER_PP_FN(8fn(8S, 8C, \
                  8seq_fold(8fn(8A, 8O, 0ppasm_expand_macro(8O, 8A)), \
                            8C, \
                            8S)))

#define ORDER_PP_DEF_0ppasm_expand_macro_tup \
  ORDER_PP_FN(8fn(8T, 8C, 0ppasm_expand_macro_seq(8tuple_to_seq(8T), 8C)))

#define ORDER_PP_DEF_0ppasm_parse \
  ORDER_PP_FN(8fn(8S,\
		  8seq_fold(8fn(8C, 8O, \
				8cond((8is_tuple(8O), 0ppasm_expand_macro_tup(8O, 8C)) \
				      (8else, 0ppasm_process_insn(8O, 8C)))), \
			    0ppasm_asm_ctx_nil, \
			    8S)))

#define ORDER_PP_DEF_0ppasm_generate_insn_bytes \
	ORDER_PP_FN(8fn(8C, \
					8seq_fold(8fn(8A, 8E, \
								  8seq_join(8A, 8ap(0ppasm_asm_ctx_entry_get_code_gen(8E), 8C))), \
							  8seq, \
							  0ppasm_asm_ctx_get_entries(8C))))


#define ORDER_PP_DEF_0ppasm_emit_insn_bytes \
  ORDER_PP_FN(8fn(8S, \
		  8stringize(						\
			     8seq_fold(8fn(8A, 8B, \
					   8adjacent(8A, \
						     8cat(8quote(PPASM_ESCAPE_BYTE_), 8B))), \
				       8nil,				\
				       8S))))


#define ORDER_PP_DEF_0assemble \
  ORDER_PP_FN(8fn(8T, \
  		  8let((8P, 0ppasm_parse(8tuple_to_seq(8T))), \
				0ppasm_emit_insn_bytes(0ppasm_generate_insn_bytes(8P)))))

#define assemble(...) ORDER_PP(0assemble(8((__VA_ARGS__))))