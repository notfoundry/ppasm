
#define ORDER_PP_DEF_8is_fn \
    ORDER_PP_FN(8fn(8F, \
                    8and( \
                        8is_tuple(8F), \
                        8not(8equal(8tuple_size(8F), 1)), \
                        8is_nil(8tuple_at(0, 8F)))))
                        