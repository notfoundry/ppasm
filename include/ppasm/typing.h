
#define ORDER_PP_SYM_0typed_tag(...) __VA_ARGS__

#define ORDER_PP_DEF_0typed \
  ORDER_PP_FN(8fn(8T, 8X, \
                  8if(8is_sym(8T), \
                      8seq(8(0typed_tag), 8T, 8X), \
                      8exit(0))))

#define ORDER_PP_DEF_0is_typed \
  ORDER_PP_FN(8fn(8X, 8and( \
                           8is_seq(8X), \
                           8equal(8seq_size(8X), 3), \
                           8same(8seq_at(0, 8X), 8(0typed_tag)), \
                           8is_sym(8seq_at(1, 8X)))))

#define ORDER_PP_DEF_0has_type \
  ORDER_PP_FN(8fn(8T, 8X, \
                  8and(0is_typed(8X), \
                       8is_sym(8T), \
                       8same(8seq_at(1, 8X), 8T))))

#define ORDER_PP_DEF_0untyped \
  ORDER_PP_FN(8fn(8X, \
                  8if(0is_typed(8X), 8seq_at(2, 8X), 8exit(0))))
