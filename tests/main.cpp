#include <gtest/gtest.h>
#include <math.h>
#include "my_set.h"

TEST(TestConstructorsSet, Default) {
    my_stl::Set<int> s;
    EXPECT_EQ(s.size(), 0);
    EXPECT_EQ(s.begin().getPtr(), nullptr);
}
