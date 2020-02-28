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


#define ORDER_PP_DEF_0ppasm_insn_jmp_generate_bytes \
	ORDER_PP_FN(8fn(8O, 8C, \
					8cond((0signed_int_sign(8O), \
						   8let((8N, 0bin_2s_complement(0bin_extend(0nat_to_based(0signed_int_num(8O), 2), 32))), \
								8seq_push_front(8nat(2,3,3), 8seq_map(0based_to_nat, 0bin_arrange_in(8, 8N))))) \
						  (8else, \
						   8let((8N, 0bin_extend(0nat_to_based(0signed_int_num(8O), 2), 32)), \
								8seq_push_front(8nat(2,3,3), 8seq_map(0based_to_nat, 0bin_arrange_in(8, 8N))))))))

#define ORDER_PP_DEF_0ppasm_insn_jmp_to_offset \
	ORDER_PP_FN(8fn(8O, 8C, \
					0ppasm_asm_ctx_entry_from(8fn(8R, \
												  0ppasm_insn_jmp_generate_bytes(8O, 8R)), \
											  5)))

#define ORDER_PP_DEF_0ppasm_insn_jmp_to_label \
	ORDER_PP_FN(8fn(8L, 8C, \
					0ppasm_asm_ctx_entry_from(8fn(8R, \
												  0ppasm_insn_jmp_generate_bytes(\
																				 0ppasm_asm_ctx_get_label_offset(8L, 8R), \
																				 8R)), \
											  5)))

#define ORDER_PP_DEF_0jmp \
	ORDER_PP_FN(8fn(8T, 8C, \
					8cond((0ppasm_is_label_reference(8T), 0ppasm_insn_jmp_to_label(8T, 8C)) \
						  (8is_num(8T), 0ppasm_insn_jmp_to_offset(0signed_int(8T, 8false), 8C)) \
						  (0is_signed_int(8T), 0ppasm_insn_jmp_to_offset(8T, 8C)) \
						  (8else, 8exit(0)))))

#define ORDER_PP_DEF_0inc \
  ORDER_PP_FN(8fn(8R, 8C,			\
  				8let((8S, 8cat(8(PPASM_REGISTER_SIZE_), 8R)) \
					   (8I, 8cat(8(PPASM_REGISTER_INDEX_), 8R)) \
					   (8B, 8cat(8(PPASM_REGISTER_BLOCK_), 8R)), \
				  	8cond( \
						  (8and(8equal(8S, 64), 8equal(8B, 0)), \
						   8seq(8to_lit(8nat(7,2)), 8to_lit(8nat(2,5,5)), 8to_lit(8add(8nat(1,9,2), 8I)))) \
						  (8and(8equal(8S, 32), 8equal(8B, 0)), \
						   8seq(8to_lit(8nat(2,5,5)), 8to_lit(8add(8nat(1,9,2), 8I)))) \
						  (8and(8equal(8S, 64), 8equal(8B, 1)), \
						   8seq(8to_lit(8nat(7,3)), 8to_lit(8nat(2,5,5)), 8to_lit(8add(8nat(1,9,2), 8I)))) \
						  (8and(8equal(8S, 32), 8equal(8B, 1)), \
						   8seq(8to_lit(8nat(6,5)), 8to_lit(8nat(2,5,5)), 8to_lit(8add(8nat(1,9,2), 8I)))) \
						  (8else, 8exit(0))))))

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
		  0ppasm_asm_ctx_entry( \
				  8seq(8to_lit(8nat(1, 9, 5))))))



#define ORDER_PP_DEF_0label \
  ORDER_PP_FN(8fn(8L, 8I, 8C, 				\
		  0ppasm_asm_ctx_entry( \
				  8seq(8to_lit(8nat(1, 9, 5))))))

#define ORDER_PP_DEF_0ppasm_is_label_reference \
	ORDER_PP_FN(8fn(8T, 8false))



#define ORDER_PP_DEF_0ppasm_asm_ctx_nil ORDER_PP_CONST(()()())

#define ORDER_PP_DEF_0ppasm_asm_ctx_get_entries \
	ORDER_PP_FN(8fn(8C, 8seq_at(0, 8C)))

#define ORDER_PP_DEF_0ppasm_asm_ctx_set_entries \
	ORDER_PP_FN(8fn(8E, 8C, 8seq_set(0, 8C, 8E)))

#define ORDER_PP_DEF_0ppasm_asm_ctx_add_entry \
	ORDER_PP_FN(8fn(8E, 8C, \
					8let((8L, 0ppasm_asm_ctx_get_entries(8C)), \
						 0ppasm_asm_ctx_set_entries(8seq_push_back(8E, 8L), 8C))))


#define ORDER_PP_DEF_0ppasm_asm_ctx_entry_nil() ORDER_PP_MACRO(8env_nil)

#define ORDER_PP_DEF_0ppasm_asm_ctx_entry_from \
	ORDER_PP_FN(8fn(8G, 8S, \
					0ppasm_asm_ctx_entry_set_code_gen(8G, \
					0ppasm_asm_ctx_entry_set_byte_length(8S, \
					0ppasm_asm_ctx_entry_nil()))))

#define ORDER_PP_DEF_0ppasm_asm_ctx_entry_set_label() \
	ORDER_PP_FN(8fn(8L, 0ppasm_asm_ctx_entry_set(8(8L), 0ppasm_pse_nil(), 8L)))

#define ORDER_PP_DEF_0ppasm_asm_ctx_entry_set		\
  ORDER_PP_FN(8fn(8S, 8C, 8X, 8env_bind(8S, 8C, 8X)))

#define ORDER_PP_DEF_0ppasm_asm_ctx_entry_get              \
  ORDER_PP_FN(8fn(8S, 8C, 8env_ref(8S, 8C)))




#define ORDER_PP_DEF_0ppasm_eval \
  ORDER_PP_FN(8fn(8F, 8eval(8env_nil, 8F)))

#define ORDER_PP_DEF_0ppasm_process_insn \
  ORDER_PP_FN(8fn(8O, 8C, \
		  8seq_join( \
			    8C,						\
			    8ap(0ppasm_eval(8O), 8C))))

#define ORDER_PP_DEF_0ppasm_expand_macro \
  ORDER_PP_FN(8fn(8M, 8C, \
		  8let((8R, 0ppasm_eval(8M)), \
		  	   8cond((8is_fn(8R), 8ap(8R, 8C)) \
				 	 (8else, 8seq_fold(8fn(8A, 8O, 8seq_join(8A, 8ap(8O, 8C))),	\
										8seq,					\
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
				8P)))

#define assemble(...) ORDER_PP(0assemble(8((__VA_ARGS__))))