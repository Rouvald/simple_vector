#include "utils.hpp"
#include <gtest/gtest.h>

TEST(test_utils, assert_with_msg)
{
    // @todo: find way to check printing string
    EXPECT_TRUE(utils::assert_with_msg(true, "true msg"));
    EXPECT_FALSE(utils::assert_with_msg(false, "false msg"));
}

TEST(test_utils, calculate_capacity)
{
    EXPECT_EQ(utils::calculate_capacity(0), 0);
    EXPECT_EQ(utils::calculate_capacity(1), 1);
    EXPECT_EQ(utils::calculate_capacity(10), 15);
}