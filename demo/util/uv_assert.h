#pragma once



/* Die with fatal error. */
#define FATAL(msg)                                        \
  do {                                                    \
    fprintf(stderr,                                       \
            "Fatal error in %s on line %d: %s\n",         \
            __FILE__,                                     \
            __LINE__,                                     \
            msg);                                         \
    fflush(stderr);                                       \
    abort();                                              \
  } while (0)

#define ASSERT(expr)                                      \
 do {                                                     \
  if (!(expr)) {                                          \
    fprintf(stderr,                                       \
            "Assertion failed in %s on line %d: %s\n",    \
            __FILE__,                                     \
            __LINE__,                                     \
            #expr);                                       \
    abort();                                              \
  }                                                       \
 } while (0)


#define ASSERT_BASE(a, operator, b, type, conv)              \
 do {                                                        \
  volatile type eval_a = (type) (a);                         \
  volatile type eval_b = (type) (b);                         \
  if (!(eval_a operator eval_b)) {                           \
    fprintf(stderr,                                          \
            "Assertion failed in %s on line %d: `%s %s %s` " \
            "(%"conv" %s %"conv")\n",                        \
            __FILE__,                                        \
            __LINE__,                                        \
            #a,                                              \
            #operator,                                       \
            #b,                                              \
            eval_a,                                          \
            #operator,                                       \
            eval_b);                                         \
    abort();                                                 \
  }                                                          \
 } while (0)

#define ASSERT_BASE_STR(expr, a, operator, b, type, conv)      \
 do {                                                          \
  if (!(expr)) {                                               \
    fprintf(stderr,                                            \
            "Assertion failed in %s on line %d: `%s %s %s` "   \
            "(%"conv" %s %"conv")\n",                          \
            __FILE__,                                          \
            __LINE__,                                          \
            #a,                                                \
            #operator,                                         \
            #b,                                                \
            (type)a,                                           \
            #operator,                                         \
            (type)b);                                          \
    abort();                                                   \
  }                                                            \
 } while (0)

#define ASSERT_BASE_LEN(expr, a, operator, b, conv, len)     \
 do {                                                        \
  if (!(expr)) {                                             \
    fprintf(stderr,                                          \
            "Assertion failed in %s on line %d: `%s %s %s` " \
            "(%.*"#conv" %s %.*"#conv")\n",                  \
            __FILE__,                                        \
            __LINE__,                                        \
            #a,                                              \
            #operator,                                       \
            #b,                                              \
            (int)len,                                        \
            a,                                               \
            #operator,                                       \
            (int)len,                                        \
            b);                                              \
    abort();                                                 \
  }                                                          \
 } while (0)

#define ASSERT_BASE_HEX(expr, a, operator, b, size)            \
 do {                                                          \
  if (!(expr)) {                                               \
    int i;                                                     \
    unsigned char* a_ = (unsigned char*)a;                     \
    unsigned char* b_ = (unsigned char*)b;                     \
    fprintf(stderr,                                            \
            "Assertion failed in %s on line %d: `%s %s %s` (", \
            __FILE__,                                          \
            __LINE__,                                          \
            #a,                                                \
            #operator,                                         \
            #b);                                               \
    for (i = 0; i < size; ++i) {                               \
      if (i > 0) fprintf(stderr, ":");                         \
      fprintf(stderr, "%02X", a_[i]);                          \
    }                                                          \
    fprintf(stderr, " %s ", #operator);                        \
    for (i = 0; i < size; ++i) {                               \
      if (i > 0) fprintf(stderr, ":");                         \
      fprintf(stderr, "%02X", b_[i]);                          \
    }                                                          \
    fprintf(stderr, ")\n");                                    \
    abort();                                                   \
  }                                                            \
 } while (0)

#define ASSERT_EQ(a, b) ASSERT_BASE(a, ==, b, int64_t, PRId64)
#define ASSERT_GE(a, b) ASSERT_BASE(a, >=, b, int64_t, PRId64)
#define ASSERT_GT(a, b) ASSERT_BASE(a, >, b, int64_t, PRId64)
#define ASSERT_LE(a, b) ASSERT_BASE(a, <=, b, int64_t, PRId64)
#define ASSERT_LT(a, b) ASSERT_BASE(a, <, b, int64_t, PRId64)
#define ASSERT_NE(a, b) ASSERT_BASE(a, !=, b, int64_t, PRId64)

#define ASSERT_UINT64_EQ(a, b) ASSERT_BASE(a, ==, b, uint64_t, PRIu64)
#define ASSERT_UINT64_GE(a, b) ASSERT_BASE(a, >=, b, uint64_t, PRIu64)
#define ASSERT_UINT64_GT(a, b) ASSERT_BASE(a, >, b, uint64_t, PRIu64)
#define ASSERT_UINT64_LE(a, b) ASSERT_BASE(a, <=, b, uint64_t, PRIu64)
#define ASSERT_UINT64_LT(a, b) ASSERT_BASE(a, <, b, uint64_t, PRIu64)
#define ASSERT_UINT64_NE(a, b) ASSERT_BASE(a, !=, b, uint64_t, PRIu64)

#define ASSERT_DOUBLE_EQ(a, b) ASSERT_BASE(a, ==, b, double, "f")
#define ASSERT_DOUBLE_GE(a, b) ASSERT_BASE(a, >=, b, double, "f")
#define ASSERT_DOUBLE_GT(a, b) ASSERT_BASE(a, >, b, double, "f")
#define ASSERT_DOUBLE_LE(a, b) ASSERT_BASE(a, <=, b, double, "f")
#define ASSERT_DOUBLE_LT(a, b) ASSERT_BASE(a, <, b, double, "f")
#define ASSERT_DOUBLE_NE(a, b) ASSERT_BASE(a, !=, b, double, "f")

#define ASSERT_STR_EQ(a, b) \
  ASSERT_BASE_STR(strcmp(a, b) == 0, a, == , b, char*, "s")

#define ASSERT_STR_NE(a, b) \
  ASSERT_BASE_STR(strcmp(a, b) != 0, a, !=, b, char*, "s")

#define ASSERT_MEM_EQ(a, b, size) \
  ASSERT_BASE_LEN(memcmp(a, b, size) == 0, a, ==, b, s, size)

#define ASSERT_MEM_NE(a, b, size) \
  ASSERT_BASE_LEN(memcmp(a, b, size) != 0, a, !=, b, s, size)

#define ASSERT_MEM_HEX_EQ(a, b, size) \
  ASSERT_BASE_HEX(memcmp(a, b, size) == 0, a, ==, b, size)

#define ASSERT_MEM_HEX_NE(a, b, size) \
  ASSERT_BASE_HEX(memcmp(a, b, size) != 0, a, !=, b, size)

#define ASSERT_NULL(a) \
  ASSERT_BASE(a, ==, NULL, void*, "p")

#define ASSERT_NOT_NULL(a) \
  ASSERT_BASE(a, !=, NULL, void*, "p")

#define ASSERT_PTR_EQ(a, b) \
  ASSERT_BASE(a, ==, b, void*, "p")

#define ASSERT_PTR_NE(a, b) \
  ASSERT_BASE(a, !=, b, void*, "p")