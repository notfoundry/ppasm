
#define ORDER_PP_DEF_0based_bin_bitnot \
  ORDER_PP_FN(8fn(8N, \
				  0based_int(8seq_map(8fn(8D,		\
										  8if(8is_0(8D), 1, 0)),	\
									  0based_int_num(8N)), \
							 0based_int_base(8N))))

#define ORDER_PP_DEF_0based_bin_2s_complement \
  ORDER_PP_FN(8fn(8N, \
				  0nat_to_based(8add(0based_to_nat(0based_bin_bitnot(8N)), 1), 2)))


#define ORDER_PP_DEF_0based_bin_extend	\
  ORDER_PP_FN(8fn(8N, 8K, \
				  8lets((8M, 0based_int_num(8N))(8S, 8seq_size(8M)),	\
						8if(8greater(8S, 8K), \
							8exit_fmt(8tuple(8(tried to truncate bitwidth of), 8M, 8(from), 8to_lit(8S), 8(to), 8to_lit(8K))), \
							8let((8D, 8sub(8K, 8S)), \
								 0based_int(8seq_join(8M, 8seq_map(8fn(8I, 0), 8seq_iota(0, 8D))), 0based_int_base(8N)))))))
