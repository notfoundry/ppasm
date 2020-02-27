
#define ORDER_PP_DEF_8exit_fmt		\
  ORDER_PP_FN(8fn(8S, \
                  8exit(8seq_fold(8fn(8A, 8X, 8separate(8A, 8X)),	\
                                  8nil,					\
                                  8if(8is_tuple(8S), \
                                      8tuple_to_seq(8S), \
                                      8S)))))

#define ORDER_PP_DEF_8is_fn \
    ORDER_PP_FN(8fn(8F, \
                    8and( \
                        8is_tuple(8F), \
                        8not(8equal(8tuple_size(8F), 1)), \
                        8is_nil(8tuple_at(0, 8F)))))

#define ORDER_PP_DEF_8is_num \
    ORDER_PP_FN(8fn(8X, \
                    8or( \
                         8is_lit(8X), \
                         8and(8is_seq(8X)))))
