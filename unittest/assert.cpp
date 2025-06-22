#include "assert.hpp"
#include <gtest/gtest.h>

#ifdef LOCAL_DEBUG
TEST(Assertion, Macro) {
  ASSERT_NO_THROW(CL_ASSERT(true));
  ASSERT_THROW(CL_ASSERT(false), std::logic_error);
}
#else
TEST(Assertion, Macro) {
  CL_ASSERT(true);
  ASSERT_DEATH(CL_ASSERT(false), ".");
}
#endif
