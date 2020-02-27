
#define ORDER_PP_SYM_0based_int(...) __VA_ARGS__

#define ORDER_PP_DEF_0based_int \
  ORDER_PP_FN(8fn(8N, 8B, 0typed(8(0based_int), 8seq(8B, 8N))))

#define ORDER_PP_DEF_0is_based_int \
  ORDER_PP_FN(8fn(8N, 8and(0has_type(8(0based_int), 8N),  \
			   8let((8M, 0untyped(8N)),    \
				8and(8is_seq(8M), 8equal(8seq_size(8M), 2))))))

#define ORDER_PP_DEF_0based_int_base \
  ORDER_PP_FN(8fn(8N, 8seq_at(0, 0untyped(8N))))

#define ORDER_PP_DEF_0based_int_num \
  ORDER_PP_FN(8fn(8N, 8seq_at(1, 0untyped(8N))))



#define ORDER_PP_DEF_0based_to_nat_impl \
  ORDER_PP_FN(8fn(8N, 8B, 8E, 8A,       \
		  8if(8seq_is_nil(8N), \
		      8A, \
		      0based_to_nat_impl(8seq_tail(8N), 8B, 8inc(8E), 8add(8mul(8seq_head(8N), 8pow(8B, 8E)), 8A)))))

#define ORDER_PP_DEF_0based_to_nat \
  ORDER_PP_FN(8fn(8N, \
		  0based_to_nat_impl(0based_int_num(8N), 0based_int_base(8N), 0, 0)))


#define ORDER_PP_DEF_0nat_to_based_impl \
  ORDER_PP_FN(8fn(8N, 8B, 8A, \
		  8if(8is_0(8N), \
		      8A, \
		      0nat_to_based_impl(8div(8N, 8B), 8B, 8seq_push_back(8to_lit(8remainder(8N, 8B)), 8A)))))

#define ORDER_PP_DEF_0nat_to_based \
  ORDER_PP_FN(8fn(8N, 8B,					\
	      8let((8M, 8if(8is_lit(8N), 8lit_to_nat(8N), 8N)),	\
		   0based_int(0nat_to_based_impl(8M, 8B, 8seq), 8B))))
