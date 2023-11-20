#include<gtest/gtest.h>
#include<vector>

#include"forward_list.hpp"
#include"allocator.hpp"

const int max_count = 100000;

template<typename T>
using my_forward_list_allocator = lab::Allocator<lab::Node<T>, max_count>;

template<typename T>
using my_forward_list = lab::forward_list<T, my_forward_list_allocator<T>>;

TEST(TestForwardList, TestCountValueConstructor) {
    my_forward_list<int> f(7, 2);
    
    int cnt = 0;
    bool flag = true;

    for(auto el : f) {
        if(el != 2) {
            flag = false;
            break;
        }
        cnt++;
    }

    if(cnt != 7) {
        flag = false;
    }


    EXPECT_EQ(flag, true);
}

TEST(TestForwardList, TestCountDefaultValueConstructor) {
    my_forward_list<int> f(20);

    int cnt = 0;
    bool flag = true;

    for(auto el : f) {
        if(el != 0) {
            flag = false;
            break;
        }
        cnt++;
    }

    if(cnt != 20) {
        flag = false;
    }

    EXPECT_EQ(flag, true);
}

TEST(TestForwardList, TestTwoIteratorsConstructor) {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};

    my_forward_list<int> f(v.begin(), v.end());

    int cnt = 0;
    bool flag = true;

    for(auto el : f) {
        if(el != v[cnt]) {
            flag = false;
            break;
        }
        cnt++;
    }

    if(cnt != v.size()) {
        flag = false;
    }

    EXPECT_EQ(flag, true);
}
TEST(TestForwardList, TestInitializerListConstructor) {
    std::initializer_list<char> list = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

    my_forward_list<char> f = list;

    int cnt = 0;
    bool flag = true;

    for(auto el : f) {
        if(el != *(list.begin() + cnt)) {
            flag = false;
            break;
        }
        cnt++;
    }

    if(cnt != list.size()) {
        flag = false;
    }

    EXPECT_EQ(flag, true);
}

TEST(TestForwardList, TestCopyConstructor) {

    my_forward_list<int> other = {1, 2, 3, 4, 5, 6};
    my_forward_list<int> f(other);

    auto it1 = other.begin();
    auto it2 = f.begin();

    bool flag = true;
    int cnt = 0;

    while(it1 != other.end() && it2 != f.end()) {

        if (*it1 != *it2) {
            flag = false;
            break;
        }

        ++it1;
        ++it2;
        ++cnt;
    }

    flag = (cnt == 6) && flag;

    EXPECT_EQ(flag, true);
}

TEST(TestForwardList, TestAssignmentOperator) {
    my_forward_list<int> other = {1, 2, 3, 4, 5, 6, 7, 8};
    my_forward_list<int> f = other;

    auto it1 = other.begin();
    auto it2 = f.begin();

    bool flag = true;
    int cnt = 0;

    while(it1 != other.end() && it2 != f.end()) {

        if (*it1 != *it2) {
            flag = false;
            break;
        }

        ++it1;
        ++it2;
        ++cnt;
    }

    flag = (cnt == 8) && flag;

    EXPECT_EQ(flag, true);
}

TEST(TestForwardList, TestEqualOperator) {
    my_forward_list<int> f1 = {1, 2, 3, 4, 5, 6, 7, 8};
    my_forward_list<int> f2 = {1, 2, 3, 4, 5, 6, 7, 8};

    ASSERT_TRUE(f1 == f2);

    f2 = {1, 2, 3, 4};

    ASSERT_FALSE(f1 == f2);
}

TEST(TestForwardList, TestNotEqualOperator) {
    my_forward_list<int> f1 = {1, 2, 3, 4, 5, 6, 7, 8};
    my_forward_list<int> f2 = {1, 2, 3, 4, 5, 6, 7, 8};

    ASSERT_FALSE(f1 != f2);

    f2 = {1, 2, 3, 4};

    ASSERT_TRUE(f1 != f2);
}

TEST(TestForwardList, TestAssignCountValues) {

    my_forward_list<int> f = {1, 2, 3, 4};
    f.assign(5, 2);

    EXPECT_EQ(f, my_forward_list<int>(5, 2));    
}

TEST(TestForwardList, TestAssignTwoIterators) {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    my_forward_list<int> f(10);

    f.assign(v.begin(), v.end());
    EXPECT_EQ(f, my_forward_list<int>(v.begin(), v.end()));
}

TEST(TestForwardList, TestAssignInitializerList) {
    std::initializer_list<int> list = {1, 2, 3, 4, 5, 6, 7, 8};
    my_forward_list<int> f(20);

    f.assign(list);
    EXPECT_EQ(f, my_forward_list<int>(list));
}

TEST(TestForwardList, TestEmpty) {
    my_forward_list<int> f;
    ASSERT_TRUE(f.empty());
    f = {1, 2, 3, 4, 5};
    ASSERT_FALSE(f.empty());
}

TEST(TestForwardList, TestLenght) {
    my_forward_list<int> f;
    ASSERT_TRUE(f.lenght() == 0);

    f = {1, 2, 3};
    ASSERT_TRUE(f.lenght() == 3);
}

TEST(TestForwardList, TestClear) {
    my_forward_list<int> f = {1, 2, 3, 4, 5, 6, 7, 8};
    f.clear();
    ASSERT_TRUE(f.empty());
}

TEST(TestForwardList, TestInsertAfterPosValue) {
    my_forward_list<int> f = {1, 2, 3, 4, 5, 6, 7, 8};
    f.insert_after(f.begin(), 5);
    EXPECT_EQ(f, my_forward_list<int>({1, 5, 2, 3, 4, 5, 6, 7, 8}));

    f.insert_after(f.before_begin(), 10);
    EXPECT_EQ(f, my_forward_list<int>({10, 1, 5, 2, 3, 4, 5, 6, 7, 8}));
}

TEST(TestForwardList, TestInsertAfterPosTwoIterators) {
    std::vector<int> v = {4, 5, 6};
    my_forward_list<int> f = {1, 2, 3};
    f.insert_after(f.before_begin(), v.begin(), v.end());
    EXPECT_EQ(f, my_forward_list<int>({4, 5, 6, 1, 2, 3}));
}

TEST(TestForwardList, TestInsertAfterPosInitializerList) {
    std::initializer_list<int> list = {1, 2, 3, 4, 5, 6};
    my_forward_list<int> f = {1, 2, 3, 4, 5, 6, 7, 8};
    f.insert_after(f.before_begin(), list);
    EXPECT_EQ(f, my_forward_list<int>({1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 7, 8}));
}

TEST(TestForwardList, TestEraseAfterPos) {
    my_forward_list<int> f = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    f.erase_after(f.before_begin());

    EXPECT_EQ(f, my_forward_list<int>({2, 3, 4, 5, 6, 7, 8, 9}));

    f.erase_after(f.begin());

    EXPECT_EQ(f, my_forward_list<int>({2, 4, 5, 6, 7, 8, 9}));
}

TEST(TestForwardList, TestEraseAfterBetweenTwoIterators) {
    my_forward_list<int> f= {1, 2, 3, 4, 5};
    std::vector<int> v = {10, 11, 12};
    f.insert_after(f.before_begin(), v.begin(), v.end());
    EXPECT_EQ(f, my_forward_list<int>({10, 11, 12, 1, 2, 3, 4, 5}));
}

TEST(TestForwardList, TestPushFront) {
    my_forward_list<int> f = {1, 2, 3, 4, 5};
    f.push_front(10);
    EXPECT_EQ(f, my_forward_list<int>({10, 1, 2, 3, 4, 5}));

    f.push_front(11);
    EXPECT_EQ(f, my_forward_list<int>({11, 10, 1, 2, 3, 4, 5}));
}

TEST(TestForwardList, TestPopFront) {
    my_forward_list<int> f = {1, 2, 3, 4, 5};
    f.pop_front();
    EXPECT_EQ(f, my_forward_list<int>({2, 3, 4, 5}));

    f.pop_front();
    EXPECT_EQ(f, my_forward_list<int>({3, 4, 5}));
}