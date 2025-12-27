#include <gtest/gtest.h>

// Простейший тест для проверки gtest
TEST(SimpleTest, BasicAssertions) {
    EXPECT_EQ(1 + 1, 2);
    EXPECT_TRUE(true);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
