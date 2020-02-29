
#define ORDER_PP_DEF_0byte ORDER_PP_FN(8fn(8T, 0typed(8(0ppasm_byte_indop), 0ppasm_indop_parse(8T))))
#define ORDER_PP_SYM_0ppasm_byte_indop(...) __VA_ARGS__

#define ORDER_PP_DEF_0word ORDER_PP_FN(8fn(8T, 0typed(8(0ppasm_word_indop), 0ppasm_indop_parse(8T))))
#define ORDER_PP_SYM_0ppasm_word_indop(...) __VA_ARGS__

#define ORDER_PP_DEF_0dword ORDER_PP_FN(8fn(8T, 0typed(8(0ppasm_dword_indop), 0ppasm_indop_parse(8T))))
#define ORDER_PP_SYM_0ppasm_dword_indop(...) __VA_ARGS__

#define ORDER_PP_DEF_0qword ORDER_PP_FN(8fn(8T, 0typed(8(0ppasm_qword_indop), 0ppasm_indop_parse(8T))))
#define ORDER_PP_SYM_0ppasm_qword_indop(...) __VA_ARGS__

#define ORDER_PP_DEF_0ppasm_is_indop \
  ORDER_PP_FN(8fn(8X, \
				  8seq_exists(8fn(8S, 0has_type(8S, 8X)), \
								  8seq(8(0ppasm_byte_indop), 8(0ppasm_word_indop), 8(0ppasm_dword_indop), 8(0ppasm_qword_indop)))))


#define ORDER_PP_DEF_0ppasm_indop_env_has_offset ORDER_PP_FN(8fn(8E, 8env_has(8(8O), 8E)))
#define ORDER_PP_DEF_0ppasm_indop_env_set_offset ORDER_PP_FN(8fn(8O, 8E, 8env_bind(8(8O), 8E, 8O)))
#define ORDER_PP_DEF_0ppasm_indop_env_get_offset ORDER_PP_FN(8fn(8E, 8env_ref(8(8O), 8E)))

#define ORDER_PP_DEF_0ppasm_indop_env_has_base ORDER_PP_FN(8fn(8E, 8env_has(8(8B), 8E)))
#define ORDER_PP_DEF_0ppasm_indop_env_set_base ORDER_PP_FN(8fn(8B, 8E, 8env_bind(8(8B), 8E, 8B)))
#define ORDER_PP_DEF_0ppasm_indop_env_get_base ORDER_PP_FN(8fn(8E, 8env_ref(8(8B), 8E)))

#define ORDER_PP_DEF_0ppasm_indop_env_has_index ORDER_PP_FN(8fn(8E, 8env_has(8(8I), 8E)))
#define ORDER_PP_DEF_0ppasm_indop_env_set_index ORDER_PP_FN(8fn(8R, 8S, 8E, 8env_bind(8(8I), 8E, 8seq(8R, 8S))))
#define ORDER_PP_DEF_0ppasm_indop_env_get_index ORDER_PP_FN(8fn(8E, 8env_ref(8(8I), 8E)))


#define ORDER_PP_DEF_0ppasm_indop_parse_index_scale \
  ORDER_PP_FN(8fn(8S, \
		  8let((8L, 8seq_filter(8fn(8X, 8or(8is_lit(8X), 8is_seq(8X))), 8S)),			\
		       8seq_head(8L))))

#define	ORDER_PP_DEF_0ppasm_indop_parse_index_reg \
  ORDER_PP_FN(8fn(8S, \
                  8let((8I, 8seq_filter(8is_sym, 8S)),                   \
                       8seq_head(8I))))

#define ORDER_PP_DEF_0ppasm_indop_parse_index \
  ORDER_PP_FN(8fn(8S, 8E, \
		  8with_assert(8equal(8seq_size(8S), 2), \
			       8let((8K, 0ppasm_indop_parse_index_scale(8S))(8R, 0ppasm_indop_parse_index_reg(8S)), \
				    0ppasm_indop_env_set_index(8R, 8K, 8E)))))

#define ORDER_PP_DEF_0ppasm_indop_parse_displacement \
  ORDER_PP_FN(8fn(8I, 8E, \
		  0ppasm_indop_env_set_offset(8I, 8E)))

#define ORDER_PP_DEF_0ppasm_indop_parse_base_or_index \
  ORDER_PP_FN(8fn(8S, 8E, \
		  8cond((8not(0ppasm_indop_env_has_base(8E)), 0ppasm_indop_env_set_base(8S, 8E)) \
			(8not(0ppasm_indop_env_has_index(8E)), 0ppasm_indop_env_set_index(8S, 1, 8E)) \
			(8else, exit(0)))))

#define ORDER_PP_DEF_0ppasm_indop_parse \
  ORDER_PP_FN(8fn(8T, \
		  8seq_fold(8fn(8E, 8X, \
				8cond((8is_tuple(8X), 8if( \
							  8not(0ppasm_indop_env_has_index(8E)), \
							  0ppasm_indop_parse_index(8tuple_to_seq(8X), 8E), \
							  8exit(0))) \
				      (8is_lit(8X), 8if( \
							8not(0ppasm_indop_env_has_offset(8E)), \
							0ppasm_indop_parse_displacement(8lit_to_nat(8X), 8E), \
							8exit(0)))	\
				      (8is_seq(8X), 8if( \
							8not(0ppasm_indop_env_has_offset(8E)), \
							0ppasm_indop_parse_displacement( \
											8eval(8env_nil, 8adjacent(8(8nat), 8seq_to_tuple(8X))), 8E), \
							8exit(0)))	\
				      (8is_sym(8X), 0ppasm_indop_parse_base_or_index(8X, 8E)) \
				      (8else, 8exit(0)))),		\
			    8env_nil,			\
			    8tuple_to_seq(8T))))
