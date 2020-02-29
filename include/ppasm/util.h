

#define ORDER_PP_IS_NAT_DIGIT_0
#define ORDER_PP_IS_NAT_DIGIT_1
#define ORDER_PP_IS_NAT_DIGIT_2
#define ORDER_PP_IS_NAT_DIGIT_3
#define ORDER_PP_IS_NAT_DIGIT_4
#define ORDER_PP_IS_NAT_DIGIT_5
#define ORDER_PP_IS_NAT_DIGIT_6
#define ORDER_PP_IS_NAT_DIGIT_7
#define ORDER_PP_IS_NAT_DIGIT_8
#define ORDER_PP_IS_NAT_DIGIT_9
#define ORDER_PP_IS_NAT_DIGIT_00
#define ORDER_PP_IS_NAT_DIGIT_01
#define ORDER_PP_IS_NAT_DIGIT_02
#define ORDER_PP_IS_NAT_DIGIT_03
#define ORDER_PP_IS_NAT_DIGIT_04
#define ORDER_PP_IS_NAT_DIGIT_05
#define ORDER_PP_IS_NAT_DIGIT_06
#define ORDER_PP_IS_NAT_DIGIT_07
#define ORDER_PP_IS_NAT_DIGIT_08
#define ORDER_PP_IS_NAT_DIGIT_09

#define ORDER_PP_DEF_8exit_fmt		\
  ORDER_PP_FN(8fn(8S, \
                  8exit(8seq_fold(8fn(8A, 8X, 8separate(8A, 8X)),	\
                                  8nil,					\
                                  8if(8is_tuple(8S), \
                                      8tuple_to_seq(8S), \
                                      8S)))))

#define ORDER_PP_DEF_8env_has \
  ORDER_PP_FN(8fn(8S, 8E, \
		  8let((8R, 8env_to_seq_of_pairs(8E)),	\
		       8let((8F, 8seq_filter(8fn(8P, 8same(8tuple_at_0(8P), 8S)), 8R)), \
			    8isnt_nil(8F)))))

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
                         8and(8is_seq(8X), 8seq_for_all(8fn(8E, \
                                                            8is_nil(8cat(8(ORDER_PP_IS_NAT_DIGIT_), 8E))), 8X)))))

