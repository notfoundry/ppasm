
#define ORDER_PP_DEF_0bin_bitnot \
  ORDER_PP_FN(8fn(8N, \
				  0based_int(8seq_map(8fn(8D,		\
										  8if(8is_0(8D), 1, 0)),	\
									  0based_int_num(8N)), \
							 0based_int_base(8N))))

#define ORDER_PP_DEF_0bin_2s_complement \
  ORDER_PP_FN(8fn(8N, \
				  0nat_to_based(8add(0based_to_nat(0bin_bitnot(8N)), 1), 2)))


#define ORDER_PP_DEF_0bin_extend	\
  ORDER_PP_FN(8fn(8N, 8K, \
				  8lets((8M, 0based_int_num(8N))(8S, 8seq_size(8M)),	\
						8if(8greater(8S, 8K), \
							8exit_fmt(8tuple(8(tried to truncate bitwidth of), 8M, 8(from), 8to_lit(8S), 8(to), 8to_lit(8K))), \
							8let((8D, 8sub(8K, 8S)), \
								 0based_int(8seq_join(8M, 8seq_map(8fn(8I, 0), 8seq_iota(0, 8D))), 0based_int_base(8N)))))))

#define ORDER_PP_DEF_0bin_arrange_in \
	ORDER_PP_FN(8fn(8K, 8N, \
					8let((8R, 8seq_fold(8fn(8A, 8B, \
								  8let((8S, 8seq_at(0, 8A))(8C, 8seq_at(1, 8A))(8T, 8seq_at(2, 8A)), \
									   8if(8is_0(8remainder(8C, 8K)), \
										   8seq(8seq_push_back(0based_int(8seq_push_back(8B, 8T), 2), 8S), 8inc(8C), 8seq), \
										   8seq(8S, 8inc(8C), 8seq_push_back(8B, 8T))))), \
							  8seq(8seq, 1, 8seq), \
							  0based_int_num(8N))), \
						 8if(8seq_isnt_nil(8seq_at(2, 8R)), \
							 8seq_push_back(8seq_at(2, 8R), 8seq_at(0, 8R)), \
							 8seq_at(0, 8R)))))
