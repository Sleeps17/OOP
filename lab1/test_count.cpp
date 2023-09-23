#include <gtest/gtest.h>
#include "count.hpp"

TEST(CountTest, CountVowelLettersTest) {
    EXPECT_EQ(count_vowels_in_word("hello"), 2);
    EXPECT_EQ(count_vowels_in_word("world"), 1);
    EXPECT_EQ(count_vowels_in_word("Hello"), -2);
    EXPECT_EQ(count_vowels_in_word(""), -1);
    EXPECT_EQ(count_vowels_in_word("aeoiu"), 5);
    EXPECT_EQ(count_vowels_in_word("my room so cute"), 6);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
