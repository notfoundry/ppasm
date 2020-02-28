
#define ORDER_PP_SYM_0signed_int(...) __VA_ARGS__

#define ORDER_PP_DEF_0signed_int \
  ORDER_PP_FN(8fn(8N, 8S, 0typed(8(0signed_int), 8seq(8S, 8N))))

#define ORDER_PP_DEF_0is_signed_int \
  ORDER_PP_FN(8fn(8N, 8and(0has_type(8(0signed_int), 8N),  \
			   8let((8M, 0untyped(8N)),    \
				8and(8is_seq(8M), 8equal(8seq_size(8M), 2))))))

#define ORDER_PP_DEF_0signed_int_sign \
  ORDER_PP_FN(8fn(8N, 8seq_at(0, 0untyped(8N))))

#define ORDER_PP_DEF_0signed_int_num \
  ORDER_PP_FN(8fn(8N, 8seq_at(1, 0untyped(8N))))
  

#define ORDER_PP_DEF_0negative \
  ORDER_PP_FN(8fn(8X, 0signed_int(8X, 8true)))

#define ORDER_PP_DEF_0positive \
  ORDER_PP_FN(8fn(8X, 0signed_int(8X, 8false)))
