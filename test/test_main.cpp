#include <gtest/gtest.h>
#include <ctime>

int main(int argc, char** argv)
{
    std::srand(std::time(nullptr));

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}