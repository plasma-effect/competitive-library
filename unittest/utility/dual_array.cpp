#include "utility/dual_array.hpp"
#include <gtest/gtest.h>

TEST(Utility, DualArrayAssignAndRead) {
  common::dual_array<int> ar(2, 3);
  ar(0, 0) = 0;
  ar(0, 1) = 1;
  ar(0, 2) = 2;
  ar(1, 0) = 3;
  ar(1, 1) = 4;
  ar(1, 2) = 5;
  ASSERT_EQ(ar(0, 0), 0);
  ASSERT_EQ(ar(0, 1), 1);
  ASSERT_EQ(ar(0, 2), 2);
  ASSERT_EQ(ar(1, 0), 3);
  ASSERT_EQ(ar(1, 1), 4);
  ASSERT_EQ(ar(1, 2), 5);
}

TEST(Utility, DualArrayAssignAndReadByAt) {
  common::dual_array<int> ar(2, 3);
  ar.at(0, 0) = 0;
  ar.at(0, 1) = 1;
  ar.at(0, 2) = 2;
  ar.at(1, 0) = 3;
  ar.at(1, 1) = 4;
  ar.at(1, 2) = 5;
  ASSERT_EQ(ar.at(0, 0), 0);
  ASSERT_EQ(ar.at(0, 1), 1);
  ASSERT_EQ(ar.at(0, 2), 2);
  ASSERT_EQ(ar.at(1, 0), 3);
  ASSERT_EQ(ar.at(1, 1), 4);
  ASSERT_EQ(ar.at(1, 2), 5);
}

TEST(Utility, DualArrayGetDimensions) {
  common::dual_array<int> ar(2, 3);
  auto [d0, d1] = ar.dimensions();
  ASSERT_EQ(d0, 2u);
  ASSERT_EQ(d1, 3u);
}

TEST(Utility, DualArrayGetSize) {
  common::dual_array<int> ar(2, 3);
  ASSERT_EQ(ar.size(), 6u);
}

TEST(Utility, DualArrayOutOfBound) {
  common::dual_array<int> ar(2, 3);
  const auto& car = ar;
#ifdef LOCAL_DEBUG
  ASSERT_THROW({ ar(2, 0); }, std::logic_error);
  ASSERT_THROW({ ar(-1, 0); }, std::logic_error);
  ASSERT_THROW({ ar(0, 4); }, std::logic_error);
  ASSERT_THROW({ ar(0, -1); }, std::logic_error);

  ASSERT_THROW({ car(2, 0); }, std::logic_error);
  ASSERT_THROW({ car(-1, 0); }, std::logic_error);
  ASSERT_THROW({ car(0, 4); }, std::logic_error);
  ASSERT_THROW({ car(0, -1); }, std::logic_error);
#else
  ASSERT_DEATH({ ar(2, 0); }, ".");
  ASSERT_DEATH({ ar(-1, 0); }, ".");
  ASSERT_DEATH({ ar(0, 4); }, ".");
  ASSERT_DEATH({ ar(0, -1); }, ".");

  ASSERT_DEATH({ car(2, 0); }, ".");
  ASSERT_DEATH({ car(-1, 0); }, ".");
  ASSERT_DEATH({ car(0, 4); }, ".");
  ASSERT_DEATH({ car(0, -1); }, ".");
#endif
  ASSERT_THROW({ ar.at(2, 0); }, std::out_of_range);
  ASSERT_THROW({ ar.at(-1, 0); }, std::out_of_range);
  ASSERT_THROW({ ar.at(0, 4); }, std::out_of_range);
  ASSERT_THROW({ ar.at(0, -1); }, std::out_of_range);

  ASSERT_THROW({ car.at(2, 0); }, std::out_of_range);
  ASSERT_THROW({ car.at(-1, 0); }, std::out_of_range);
  ASSERT_THROW({ car.at(0, 4); }, std::out_of_range);
  ASSERT_THROW({ car.at(0, -1); }, std::out_of_range);
}

TEST(Utility, DualArrayBoolAssignAndRead) {
  common::dual_array<bool> ar(2, 2);
  ar(0, 0) = true;
  ar(1, 1) = true;
  ASSERT_EQ(ar(0, 0), true);
  ASSERT_EQ(ar(0, 1), false);
  ASSERT_EQ(ar(1, 0), false);
  ASSERT_EQ(ar(1, 1), true);
}

TEST(Utility, DualArrayBoolAssignAndReadByAt) {
  common::dual_array<bool> ar(2, 2);
  ar.at(0, 0) = true;
  ar.at(1, 1) = true;
  ASSERT_EQ(ar.at(0, 0), true);
  ASSERT_EQ(ar.at(0, 1), false);
  ASSERT_EQ(ar.at(1, 0), false);
  ASSERT_EQ(ar.at(1, 1), true);
}

TEST(Utility, DualArrayBoolGetDimensions) {
  common::dual_array<bool> ar(2, 3);
  auto [d0, d1] = ar.dimensions();
  ASSERT_EQ(d0, 2u);
  ASSERT_EQ(d1, 3u);
}

TEST(Utility, DualArrayBoolGetSize) {
  common::dual_array<bool> ar(2, 3);
  ASSERT_EQ(ar.size(), 6u);
}

TEST(Utility, DualArrayBoolOutOfBound) {
  common::dual_array<bool> ar(2, 3);
  const auto& car = ar;
#ifdef LOCAL_DEBUG
  ASSERT_THROW({ ar(2, 0); }, std::logic_error);
  ASSERT_THROW({ ar(-1, 0); }, std::logic_error);
  ASSERT_THROW({ ar(0, 4); }, std::logic_error);
  ASSERT_THROW({ ar(0, -1); }, std::logic_error);

  ASSERT_THROW({ car(2, 0); }, std::logic_error);
  ASSERT_THROW({ car(-1, 0); }, std::logic_error);
  ASSERT_THROW({ car(0, 4); }, std::logic_error);
  ASSERT_THROW({ car(0, -1); }, std::logic_error);
#else
  ASSERT_DEATH({ ar(2, 0); }, ".");
  ASSERT_DEATH({ ar(-1, 0); }, ".");
  ASSERT_DEATH({ ar(0, 4); }, ".");
  ASSERT_DEATH({ ar(0, -1); }, ".");

  ASSERT_DEATH({ car(2, 0); }, ".");
  ASSERT_DEATH({ car(-1, 0); }, ".");
  ASSERT_DEATH({ car(0, 4); }, ".");
  ASSERT_DEATH({ car(0, -1); }, ".");
#endif
  ASSERT_THROW({ ar.at(2, 0); }, std::out_of_range);
  ASSERT_THROW({ ar.at(-1, 0); }, std::out_of_range);
  ASSERT_THROW({ ar.at(0, 4); }, std::out_of_range);
  ASSERT_THROW({ ar.at(0, -1); }, std::out_of_range);

  ASSERT_THROW({ car.at(2, 0); }, std::out_of_range);
  ASSERT_THROW({ car.at(-1, 0); }, std::out_of_range);
  ASSERT_THROW({ car.at(0, 4); }, std::out_of_range);
  ASSERT_THROW({ car.at(0, -1); }, std::out_of_range);
}
