#include "order/interpreter.h"

#include "byte_escapes.h"
#include "x86_register_syms.h"
#include "indirect_operand.h"
#include "keywords.h"


#define ORDER_PP_DEF_0inc \
  ORDER_PP_FN(8fn(8R, 8E,			\
  				8let((8S, 8cat(8(PPASM_REGISTER_SIZE_), 8R))(8I, 8cat(8(PPASM_REGISTER_INDEX_), 8R))(8B, 8cat(8(PPASM_REGISTER_BLOCK_), 8R)), \
				  	8cond( \
						  (8and(8equal(8S, 64), 8equal(8B, 0)), 8seq(8to_lit(8nat(7,2)), 8to_lit(8nat(2,5,5)), 8to_lit(8add(8nat(1,9,2), 8I)))) \
						  (8and(8equal(8S, 32), 8equal(8B, 0)), 8seq(8to_lit(8nat(2,5,5)), 8to_lit(8add(8nat(1,9,2), 8I)))) \
						  (8and(8equal(8S, 64), 8equal(8B, 1)), 8seq(8to_lit(8nat(7,3)), 8to_lit(8nat(2,5,5)), 8to_lit(8add(8nat(1,9,2), 8I)))) \
						  (8and(8equal(8S, 32), 8equal(8B, 1)), 8seq(8to_lit(8nat(6,5)), 8to_lit(8nat(2,5,5)), 8to_lit(8add(8nat(1,9,2), 8I)))) \
						  (8else, 8exit(0))))))

#define ORDER_PP_DEF_0push \
  ORDER_PP_FN(8fn(8R, 8E,			\
		  8seq(8to_lit(8nat(5, 5)))))

#define ORDER_PP_DEF_0pop \
  ORDER_PP_FN(8fn(8R, 8E,			\
		  8seq(8to_lit(8nat(1, 0)))))

#define ORDER_PP_DEF_0mov \
  ORDER_PP_FN(8fn(8A, 8B, 8E,			\
		  8seq(8B)))

#define ORDER_PP_DEF_0ret \
  ORDER_PP_FN(8fn(8X, 8E, 				\
		  0ppasm_make_pse( \
				  8seq(8to_lit(8nat(1, 9, 5))))))





#define ORDER_PP_DEF_0ppasm_parse_state_nil ORDER_PP_CONST()

#define ORDER_PP_DEF_0ppasm_pse_nil() ORDER_PP_MACRO(8env_nil)

#define ORDER_PP_DEF_0ppasm_make_pse \
  ORDER_PP_FN(8fn(8B, \
		  0ppasm_pse_set(8(8B), 0ppasm_pse_nil(), 8B)))

#define ORDER_PP_DEF_0ppasm_pse_set		\
  ORDER_PP_FN(8fn(8S, 8E, 8X, 8env_bind(8S, 8E, 8X)))

#define ORDER_PP_DEF_0ppasm_pse_get              \
  ORDER_PP_FN(8fn(8S, 8E, 8env_ref(8S, 8E)))




#define ORDER_PP_DEF_0ppasm_eval \
  ORDER_PP_FN(8fn(8F, 8E, 8eval(8env_nil, 8F)))

#define ORDER_PP_DEF_0ppasm_process_insn \
  ORDER_PP_FN(8fn(8O, 8E, \
		  8seq_join( \
			    8E,						\
			    8ap(0ppasm_eval(8O, 8E), 8E))))

#define ORDER_PP_DEF_0ppasm_expand_macro \
  ORDER_PP_FN(8fn(8M, 8E, \
		  8let((8R, 0ppasm_eval(8M, 8E)), \
		       8seq_fold(8fn(8A, 8O, 8seq_join(8A, 8ap(8O, 8E))),	\
				 8nil,					\
				 8cond(\
				       (8is_tuple(8R), 8tuple_to_seq(8R)) \
				       (8is_seq(8R), 8R) \
				       (8else, 8seq(8R)))))))

#define ORDER_PP_DEF_0ppasm_expand_macro_seq \
  ORDER_PP_FN(8fn(8S, 8E, \
                  8seq_fold(8fn(8A, 8O, 0ppasm_expand_macro(8O, 8A)), \
                            8E, \
                            8S)))

#define ORDER_PP_DEF_0ppasm_expand_macro_tup \
  ORDER_PP_FN(8fn(8T, 8E, 0ppasm_expand_macro_seq(8tuple_to_seq(8T), 8E)))

#define ORDER_PP_DEF_0ppasm_parse \
  ORDER_PP_FN(8fn(8S,\
		  8seq_fold(8fn(8E, 8O, \
				8cond((8is_tuple(8O), 0ppasm_expand_macro_tup(8O, 8E)) \
				      (8else, 0ppasm_process_insn(8O, 8E)))), \
			    0ppasm_parse_state_nil, \
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