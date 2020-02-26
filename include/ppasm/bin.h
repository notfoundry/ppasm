#define ORDER_PP_DEF_0base_to_nat_impl \
  ORDER_PP_FN(8fn(8N, 8B, 8E, 8A,       \
                  8if(8seq_is_nil(8N), \
                      8A, \
                      0base_to_nat_impl(8seq_tail(8N), 8B, 8inc(8E), 8add(8mul(8seq_head(8N), 8pow(8B, 8E)), 8A)))))

#define ORDER_PP_DEF_0base_to_nat \
  ORDER_PP_FN(8fn(8N, 8B, 8lit_to_nat(0base_to_nat_impl(8N, 8B, 0, 0))))


#define ORDER_PP_DEF_0nat_to_base_impl \
  ORDER_PP_FN(8fn(8N, 8B, 8A, \
                  8if(8is_0(8N), \
                      8A, \
                      0nat_to_base_impl(8div(8N, 8B), 8B, 8seq_push_back(8to_lit(8remainder(8N, 8B)), 8A)))))

#define ORDER_PP_DEF_0nat_to_base \
  ORDER_PP_FN(8fn(8N, 8B,                                       \
              8let((8M, 8if(8is_lit(8N), 8lit_to_nat(8N), 8N)), \
                   0nat_to_base_impl(8M, 8B, 8seq))))


#define ORDER_PP_DEF_0bitnot \
  ORDER_PP_FN(8fn(8N, \
                  8seq_map(8fn(8D, \
                               8if(8is_0(8D), 1, 0)),   \
                           0nat_to_base(8N, 2))))

#define ORDER_PP_DEF_0twos_complement \
  ORDER_PP_FN(8fn(8N, 8add(0base_to_nat(0bitnot(8N), 2), 1)))
