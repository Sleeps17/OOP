#include<gtest/gtest.h>
#include"four.hpp"

class FourTest: public testing::Test {

  protected:

    void SetUp() override {
        number = Four();
    }

    void TearDown() override {
        ~Four(number);
    }

    Four number;
};

// Тесты конструкторов
TEST_F(FourTest, DefaultConstructor) {
    number = Four{};
    EXPECT_EQ(number.lenght(), 0);
    EXPECT_EQ(number.capacity(), 0);
}

TEST_F(FourTest, PointerConstructor) {
    const unsigned char* num = reinterpret_cast<const unsigned char*>("1233");
    number = Four{num};

    EXPECT_EQ(number.lenght(), 4);
    EXPECT_EQ(number.capacity(), 8);
    EXPECT_EQ(number, Four{"1233"});

    num = reinterpret_cast<const unsigned char*>("1234");
    EXPECT_THROW(number = Four{num}, std::invalid_argument);

    num = nullptr;
    EXPECT_THROW(number = Four(num), std::invalid_argument);
}

TEST_F(FourTest, FillConstructor) {
    size_t _len = 3;
    unsigned char t = '3';

    number = Four(_len, t);
    EXPECT_EQ(number.lenght(), 3);
    EXPECT_EQ(number.capacity(), 6);
    EXPECT_EQ(number, Four{"333"});

    _len = 4;
    t = '4';
    EXPECT_THROW(number = Four(_len, t), std::invalid_argument);
}

TEST_F(FourTest, InitializerListConstructor) {
    std::initializer_list<unsigned char> l1 = {'1', '2', '3', '3', '2', '1'};
    
    number = Four(l1);
    EXPECT_EQ(number.lenght(), 6);
    EXPECT_EQ(number.capacity(), 12);
    EXPECT_EQ(number, Four("123321"));

    std::initializer_list<unsigned char> l2 = {};
    EXPECT_THROW(number = Four(l2), std::invalid_argument);

    std::initializer_list<unsigned char> l3 = {'4', '3', '2', '1'};
    EXPECT_THROW(number = Four(l3), std::invalid_argument);

} 

TEST_F(FourTest, StringConstructor) {
    std::string str;

    str = "1233";
    number = Four(str);
    EXPECT_EQ(number.lenght(), 4);
    EXPECT_EQ(number.capacity(), 8);
    EXPECT_EQ(number, Four{"1233"});

    str = "";
    EXPECT_THROW(number = Four(str), std::invalid_argument);

    str = "4444";
    EXPECT_THROW(number = Four(str), std::invalid_argument);
}

// Тесты оперраторов
TEST_F(FourTest, OpeartorPostIncrement) {
    number = Four{"1"};
    number++;
    EXPECT_EQ(number, Four{"2"});

    number = Four{"33"};
    number++;
    EXPECT_EQ(number, Four{"100"});

    EXPECT_EQ(number++, Four{"100"});
    EXPECT_EQ(number, Four{"101"});

    number = Four{"333333333333"};
    number++;
    EXPECT_EQ(number, Four{"1000000000000"});
}

TEST_F(FourTest, OperatorPreIncrement) {
    number = Four{"1"};
    ++number;
    EXPECT_EQ(number, Four{"2"});

    number = Four{"33"};
    ++number;
    EXPECT_EQ(number, Four{"100"});

    EXPECT_EQ(++number, Four{"101"});

    number = Four{"333333333333"};
    ++number;
    EXPECT_EQ(number, Four{"1000000000000"});
}

TEST_F(FourTest, OpeartorPostDecrement) {
    number = Four{"1"};
    number--;
    EXPECT_EQ(number, Four{"0"});

    number = Four("100");
    number--;
    EXPECT_EQ(number, Four{"33"});

    number = Four("10000");
    number--;
    EXPECT_EQ(number, Four("3333"));

    number = Four{"0"};
    ASSERT_THROW(number--, std::logic_error);
}

TEST_F(FourTest, OpeartorPreDecrement) {
    number = Four{"1"};
    --number;
    EXPECT_EQ(number, Four("0"));

    number = Four("100");
    --number;
    EXPECT_EQ(number, Four{"33"});

    EXPECT_EQ(--number, Four("32"));

    number = Four("10000");
    --number;
    EXPECT_EQ(number, Four("3333"));

    number = Four{"0"};
    ASSERT_THROW(--number, std::logic_error);
}

TEST_F(FourTest, OperatorPlusEquals) {
    number = Four("22");
    Four other = Four("12");
    number += other;
    EXPECT_EQ(number, Four("100"));

    number = Four{"33"};
    other = Four{"33"};
    number += other;
    EXPECT_EQ(number, Four{"132"});

    number = Four{"1"};
    other = Four{"3"};
    number += other;
    EXPECT_EQ(number, Four{"10"});

    number = Four{"3333333"};
    other = Four{"1111111111"};
    number += other;
    EXPECT_EQ(number, Four{"1121111110"});
}

TEST_F(FourTest, OperatorMinusEquals) {
    number = Four{"100"};
    Four other = Four{"33"};
    number -= other;
    EXPECT_EQ(number, Four{"1"});

    number = Four{"11111"};
    other = Four{"33"};
    number -= other;
    EXPECT_EQ(number, Four{"11012"});

    number = Four{"12"};
    other = Four{"0"};
    number -= other;
    EXPECT_EQ(number, Four{"12"});

    number = Four{"12"};
    other = Four{"12"};
    number -= other;
    EXPECT_EQ(number, Four{"0"});

    number = Four{"300"};
    other = Four{"1"};
    number -= other;
    EXPECT_EQ(number, Four{"233"});

    number = Four{"12"};
    other = Four{"13"};
    ASSERT_THROW(number -= other, std::logic_error);
}

TEST_F(FourTest, OperatorMultiplyEquals) {
    number = Four{"10"};
    Four other = Four{"12"};
    number *= other;
    EXPECT_EQ(number, Four{"120"});

    number = Four{"33333333333"};
    other = Four{"33333333333"};
    number *= other;
    EXPECT_EQ(number, Four{"3333333333200000000001"});

    number = Four{"12"};
    other = Four{"1"};
    number *= other;
    EXPECT_EQ(number, Four{"12"});

    number = Four{"12"};
    other = Four{"0"};
    number *= other;
    EXPECT_EQ(number, Four{"0"});

    number = Four{"0"};
    other = Four{"1"};
    number *= other;
    EXPECT_EQ(number, Four{"0"});
}

TEST_F(FourTest, OperatorDevideEquals) {
    number = Four{"33"};
    Four other = Four{"11"};
    number /= other;
    EXPECT_EQ(number, Four{"3"});

    number = Four{"3212321232123"};
    other = Four{"121212"};
    number /= other;
    EXPECT_EQ(number, Four{"21001121"});

    number = Four{"331"};
    other = Four{"1"};
    number /= other;
    EXPECT_EQ(number, Four{"331"});

    number = Four{"0"};
    other = Four{"3333333"};
    number /= other;
    EXPECT_EQ(number, Four{"0"});

    number = Four{"322"};
    other = Four{"0"};
    ASSERT_THROW(number /= other, std::logic_error);
}

TEST_F(FourTest, OperatorModulusEquals) {
    Four other;

    number = Four{"12"};
    other = Four{"3"};
    number %= other;
    EXPECT_EQ(number, Four{"0"});

    number = Four{"321231"};
    other = Four{"12"};
    number %= other;
    EXPECT_EQ(number, Four{"3"});

    number = Four{"10"};
    other = Four{"22"};
    number %= other;
    EXPECT_EQ(number, Four{"10"});

    number = Four{"100"};
    other = Four{"1"};
    number %= other;
    EXPECT_EQ(number, Four{"0"});

    number = Four{"0"};
    other = Four{"10"};
    number %= other;
    EXPECT_EQ(number, Four{"0"});

    number = Four{"10"};
    other = Four{"0"};
    ASSERT_THROW(number %= other, std::logic_error);
}

TEST_F(FourTest, OperatorEquality) {

    number = Four{"12"};
    Four other = Four{"13"};
    ASSERT_FALSE(number == other);

    number = Four{"321123"};
    other = Four{"1233"};
    ASSERT_FALSE(number == other);

    number = Four{"1000"};
    other = Four{"1000"};
    ASSERT_TRUE(number == other);

}

TEST_F(FourTest, OperatorNotEqual) {
    number = Four{"12"};
    Four other = Four{"13"};
    ASSERT_TRUE(number != other);

    number = Four{"321123"};
    other = Four{"1233"};
    ASSERT_TRUE(number != other);

    number = Four{"1000"};
    other = Four{"1000"};
    ASSERT_FALSE(number != other);
}

TEST_F(FourTest, OperatorLess) {
    number = Four{"12"};
    Four other = Four{"13"};
    ASSERT_TRUE(number < other);

    number = Four{"321123"};
    other = Four{"1233"};
    ASSERT_FALSE(number < other);

    number = Four{"1000"};
    other = Four{"1000"};
    ASSERT_FALSE(number < other);
}

TEST_F(FourTest, OperatorGreate) {
    number = Four{"12"};
    Four other = Four{"13"};
    ASSERT_FALSE(number > other);

    number = Four{"321123"};
    other = Four{"1233"};
    ASSERT_TRUE(number > other);

    number = Four{"1000"};
    other = Four{"1000"};
    ASSERT_FALSE(number > other);
}

TEST_F(FourTest, OperatorLessOrEqual) {
    number = Four{"12"};
    Four other = Four{"13"};
    ASSERT_TRUE(number <= other);

    number = Four{"321123"};
    other = Four{"1233"};
    ASSERT_FALSE(number <= other);

    number = Four{"1000"};
    other = Four{"1000"};
    ASSERT_TRUE(number <= other);
}

TEST_F(FourTest, OperatorGreateOrEqual) {
    number = Four{"12"};
    Four other = Four{"13"};
    ASSERT_FALSE(number >= other);

    number = Four{"321123"};
    other = Four{"1233"};
    ASSERT_TRUE(number >= other);

    number = Four{"1000"};
    other = Four{"1000"};
    ASSERT_TRUE(number >= other);
}

TEST_F(FourTest, OperatorPlus) {
    Four other;

    number = Four{"12"};
    other = Four{"0"};
    EXPECT_EQ(number + other, Four{"12"});

    number = Four{"333"};
    other = Four{"1"};
    EXPECT_EQ(number + other, Four{"1000"});

    number = Four{"11"};
    other = Four{"333"};
    EXPECT_EQ(number + other, Four{"1010"});

    number = Four{"1232123212321121223"};
    other = Four{"132123121213212321321"};
    EXPECT_EQ(number + other, Four{"200021311032200103210"});
}

TEST_F(FourTest, OperatorMinus) {
    number = Four{"100"};
    Four other = Four{"33"};
    EXPECT_EQ(number - other, Four{"1"});

    number = Four{"11111"};
    other = Four{"33"};
    EXPECT_EQ(number - other, Four{"11012"});

    number = Four{"12"};
    other = Four{"0"};
    EXPECT_EQ(number - other, Four{"12"});

    number = Four{"12"};
    other = Four{"12"};
    EXPECT_EQ(number - other, Four{"0"});

    number = Four{"300"};
    other = Four{"1"};
    EXPECT_EQ(number - other, Four{"233"});

    number = Four{"12"};
    other = Four{"13"};
    ASSERT_THROW(number - other, std::logic_error);
}

TEST_F(FourTest, OperatorMultiply) {
    number = Four{"10"};
    Four other = Four{"12"};
    EXPECT_EQ(number*other, Four{"120"});

    number = Four{"33333333333"};
    other = Four{"33333333333"};
    EXPECT_EQ(number*other, Four{"3333333333200000000001"});

    number = Four{"12"};
    other = Four{"1"};
    EXPECT_EQ(number*other, Four{"12"});

    number = Four{"12"};
    other = Four{"0"};
    EXPECT_EQ(number*other, Four{"0"});

    number = Four{"0"};
    other = Four{"1"};
    EXPECT_EQ(number*other, Four{"0"});
}

TEST_F(FourTest, OperatorDivide) {
    number = Four{"33"};
    Four other = Four{"11"};
    EXPECT_EQ(number / other, Four{"3"});

    number = Four{"3212321232123"};
    other = Four{"121212"};
    EXPECT_EQ(number / other, Four{"21001121"});

    number = Four{"331"};
    other = Four{"1"};
    EXPECT_EQ(number / other, Four{"331"});

    number = Four{"0"};
    other = Four{"3333333"};
    EXPECT_EQ(number / other, Four{"0"});

    number = Four{"322"};
    other = Four{"0"};
    ASSERT_THROW(number / other, std::logic_error);
}

TEST_F(FourTest, OperatorModulus) {
    Four other;

    number = Four{"12"};
    other = Four{"3"};
    EXPECT_EQ(number % other, Four{"0"});

    number = Four{"321231"};
    other = Four{"12"};
    EXPECT_EQ(number % other, Four{"3"});

    number = Four{"10"};
    other = Four{"22"};
    EXPECT_EQ(number % other, Four{"10"});

    number = Four{"100"};
    other = Four{"1"};
    EXPECT_EQ(number % other, Four{"0"});

    number = Four{"0"};
    other = Four{"10"};
    EXPECT_EQ(number % other, Four{"0"});

    number = Four{"10"};
    other = Four{"0"};
    ASSERT_THROW(number % other, std::logic_error);
}

TEST_F(FourTest, OperatorInt) {
    number = Four{"0"};
    int result = static_cast<int>(number);
    EXPECT_EQ(result, 0);

    number = Four{"1233321"};
    result = static_cast<int>(number);
    EXPECT_EQ(result, 7161);

    number = Four{"12321212321121"};
    result = static_cast<int>(number);
    EXPECT_EQ(result, 115764825);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
