#include<gtest/gtest.h>

#include "forward_list.hpp"
#include"allocator.hpp"

const int max_count = 100000;

template<typename T>
using my_forward_list_allocator = lab::Allocator<lab::Node<T>, max_count>;

template<typename T>
using my_forward_list = lab::forward_list<T, my_forward_list_allocator<T>>;

TEST(TestForwardListIterator, TestIteratorConstructor) {
    auto Node = new lab::Node<int>(5);
    Node -> next = nullptr;
    auto it = lab::forward_list<int>::iterator(Node);

    EXPECT_EQ(it.node -> data, 5);
    EXPECT_EQ(it.node -> next, nullptr);
}

TEST(TestForwardListIterator, TestIteratorOperatorStar) {
    my_forward_list<int> f = {1, 2, 3,4};

    auto it = f.begin();
    EXPECT_EQ(*it, 1);

    it = f.end();
    EXPECT_EQ(*it, 0);
}

TEST(TestForwardListIterator, TestOperatorPreIncrement) {
    my_forward_list<int> f = {1, 2, 3, 4, 5};
    auto it = f.begin();

    ++it;

    EXPECT_EQ(*it, 2);

    auto nit = ++it;

    EXPECT_EQ(*nit, 3);
}

TEST(TestForwardListIterator, TestOperatorPostIcrement) {
    my_forward_list<int> f = {1, 2, 3, 4, 5};

    auto it = f.begin();
    it++;

    EXPECT_EQ(*it, 2);

    auto nit = it++;
    EXPECT_EQ(*nit, 2);
}

TEST(TestForwardListIterator, TestOperatorPlus) {
    my_forward_list<int> f = {1, 2, 3, 4, 5, 6, 7, 8};

    auto it = f.begin();

    auto nit = it + 2;

    EXPECT_EQ(*nit, 3);

    nit = nit + 100;

    EXPECT_EQ(*nit, 0);
}

TEST(TestForwardListIterator, TestOperatorPlusEqual) {
    my_forward_list<int> f = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto it = f.begin();

    it += 3;

    EXPECT_EQ(*it, 4);

    it += 100;

    EXPECT_EQ(*it, 0);
}

TEST(TestForwardListIterator, TestOperatorEqual) {
    my_forward_list<int> f = {1, 2, 3, 4, 5};

    auto first = f.begin();
    auto second = f.begin();

    ASSERT_TRUE(first == second);

    second++;
    ASSERT_FALSE(first == second);
}


TEST(TestForwardListIterator, TestOperatorNotEqual) {
    my_forward_list<int> f = {1, 2, 3, 4, 5};

    auto first = f.begin();
    auto second = f.begin();

    ASSERT_FALSE(first != second);

    second++;
    ASSERT_TRUE(first != second);
}

TEST(TestForwardListConstIterator, TestIteratorConstructor) {
    auto Node = new lab::Node<int>(5);
    Node -> next = nullptr;
    auto it = lab::forward_list<int>::const_iterator(Node);

    EXPECT_EQ(it.node -> data, 5);
    EXPECT_EQ(it.node -> next, nullptr);
}

TEST(TestForwardListConstIterator, TestIteratorOperatorStar) {
    my_forward_list<int> f = {1, 2, 3,4};

    auto it = f.cbegin();
    EXPECT_EQ(*it, 1);

    it = f.cend();
    EXPECT_EQ(*it, 0);
}

TEST(TestForwardListConstIterator, TestOperatorPreIncrement) {
    my_forward_list<int> f = {1, 2, 3, 4, 5};
    auto it = f.cbegin();

    ++it;

    EXPECT_EQ(*it, 2);

    auto nit = ++it;

    EXPECT_EQ(*nit, 3);
}

TEST(TestForwardListConstIterator, TestOperatorPostIcrement) {
    my_forward_list<int> f = {1, 2, 3, 4, 5};

    auto it = f.cbegin();
    it++;

    EXPECT_EQ(*it, 2);

    auto nit = it++;
    EXPECT_EQ(*nit, 2);
}

TEST(TestForwardListConstIterator, TestOperatorPlus) {
    my_forward_list<int> f = {1, 2, 3, 4, 5, 6, 7, 8};

    auto it = f.cbegin();

    auto nit = it + 2;

    EXPECT_EQ(*nit, 3);

    nit = nit + 100;

    EXPECT_EQ(*nit, 0);
}

TEST(TestForwardListConstIterator, TestOperatorPlusEqual) {
    my_forward_list<int> f = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto it = f.cbegin();

    it += 3;

    EXPECT_EQ(*it, 4);

    it += 100;

    EXPECT_EQ(*it, 0);
}

TEST(TestForwardListConstIterator, TestOperatorEqual) {
    my_forward_list<int> f = {1, 2, 3, 4, 5};

    auto first = f.cbegin();
    auto second = f.cbegin();

    ASSERT_TRUE(first == second);

    second++;
    ASSERT_FALSE(first == second);
}


TEST(TestForwardListConstIterator, TestOperatorNotEqual) {
    my_forward_list<int> f = {1, 2, 3, 4, 5};

    auto first = f.cbegin();
    auto second = f.cbegin();

    ASSERT_FALSE(first != second);

    second++;
    ASSERT_TRUE(first != second);
}