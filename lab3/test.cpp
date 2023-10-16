#include<gtest/gtest.h>
#include "rhomb.hpp"
#include"trapezoid.hpp"
#include "pentagone.hpp"

class TestRhomb: public testing::Test {

  protected:
    void SetUp() override {
        r = Rhomb();
    }

    void TearDown() override {
        r.~Rhomb();
    }

    Rhomb r;

};

TEST_F(TestRhomb, TestArea) {
    Point upper(0.0, 1.0), lower(0.0, -1.0), left(-3.0, 0.0), right(3.0, 0.0);
    r = Rhomb(upper, lower, left, right, "rhomb1");
    double ans_area = 6.0;
    EXPECT_DOUBLE_EQ(r.area(), ans_area);

    upper = Point(1.0, 1.0);
    lower = Point(-1.0, -1.0);
    left = Point(-3.0, 3.0);
    right = Point(3.0, -3.0);
    r = Rhomb(upper, lower, left, right, "rhomb1");
    ans_area = 12.0;
    EXPECT_DOUBLE_EQ(r.area(), ans_area);
}

TEST_F(TestRhomb, TestPerimetr) {
    Point upper(0.0, 1.0), lower(0.0, -1.0), left(-3.0, 0.0), right(3.0, 0.0);
    r = Rhomb(upper, lower, left, right, "rhomb1");
    double ans_perimetr = 12.649110640673518;
    EXPECT_DOUBLE_EQ(r.perimetr(), ans_perimetr);

    upper = Point(1.0, 1.0);
    lower = Point(-1.0, -1.0);
    left = Point(-3.0, 3.0);
    right = Point(3.0, -3.0);
    r = Rhomb(upper, lower, left, right, "rhomb1");
    ans_perimetr = 17.888543819998318;
    EXPECT_DOUBLE_EQ(r.perimetr(), ans_perimetr);
}

TEST_F(TestRhomb, TestCenter) {
    Point upper(0.0, 1.0), lower(0.0, -1.0), left(-3.0, 0.0), right(3.0, 0.0);
    r = Rhomb(upper, lower, left, right, "rhomb1");
    Point ans = Point(0.0, 0.0);
    EXPECT_EQ(r.center(), ans);

    upper = Point(1.0, 1.0);
    lower = Point(-1.0, -1.0);
    left = Point(-3.0, 3.0);
    right = Point(3.0, -3.0);
    r = Rhomb(upper, lower, left, right, "rhomb1");
    ans = Point(0.0, 0.0);
    EXPECT_EQ(r.center(), ans);
    upper = Point(1.0, 2.0); 
    lower = Point(1.0, -2.0);
    left = Point(0.0, 0.0);
    right = Point(2.0, 0.0);
    r = Rhomb(upper, lower, left, right, "rhomb1");
    ans = Point(1.0, 0.0);
    EXPECT_EQ(r.center(), ans);
}

TEST_F(TestRhomb, TestOperatorDouble) {
    Point upper(0.0, 1.0), lower(0.0, -1.0), left(-3.0, 0.0), right(3.0, 0.0);
    r = Rhomb(upper, lower, left, right, "rhomb1");
    double ans_area = 6.0;
    EXPECT_DOUBLE_EQ(static_cast<double>(r), ans_area);

    upper = Point(1.0, 1.0);
    lower = Point(-1.0, -1.0);
    left = Point(-3.0, 3.0);
    right = Point(3.0, -3.0);
    r = Rhomb(upper, lower, left, right, "rhomb1");
    ans_area = 12.0;
    EXPECT_DOUBLE_EQ(static_cast<double>(r), ans_area);
}

TEST_F(TestRhomb, TestOperatorEqual) {
    Point upper(1.0, 2.0), lower(1.0, -2.0), left(0.0, 0.0), right(2.0, 0.0);
    Rhomb r1(upper, lower, left, right, "rhomb1");
    Rhomb r2(upper, lower, left, right, "rhomb2");
    ASSERT_TRUE(r1 == r2); 
    upper = Point(1.0, 1.0);
    lower = Point(-1.0, -1.0);
    left = Point(-3.0, 3.0);
    right = Point(3.0, -3.0);
    r2 = Rhomb(upper, lower, left, right, "rhomb2");
    ASSERT_FALSE(r1 == r2);
}

TEST_F(TestRhomb, TestOperatorNotEqual) {
  Point upper(1.0, 2.0), lower(1.0, -2.0), left(0.0, 0.0), right(2.0, 0.0);
    Rhomb r1(upper, lower, left, right, "rhomb1");
    Rhomb r2(upper, lower, left, right, "rhomb2");
    ASSERT_FALSE(r1 != r2); 
    upper = Point(1.0, 1.0);
    lower = Point(-1.0, -1.0);
    left = Point(-3.0, 3.0);
    right = Point(3.0, -3.0);
    r2 = Rhomb(upper, lower, left, right, "rhomb2");
    ASSERT_TRUE(r1 != r2);
}

class TestTrapezoid: public testing::Test {

  protected:
    
    void SetUp() override {
        t = Trapezoid();
    }

    void TearDown() override {
        t.~Trapezoid();
    }

    Trapezoid t;
};

TEST_F(TestTrapezoid, TestArea) {
    Point left_lower(0.0, 0.0), right_lower(6.0, 0.0), left_upper(2.0, 2.0), right_upper(4.0, 2.0);
    t = Trapezoid(left_lower, right_lower, left_upper, right_upper, "trapezoid");
    double ans = 10.338387;
    EXPECT_FLOAT_EQ(t.area(), ans);

    left_lower = Point(0.0, 0.0); right_lower = Point(4.0, 0.0); left_upper = Point(1.0, 2.0); right_upper = Point(4.0, 2.0);
    t = Trapezoid(left_lower, right_lower, left_upper, right_upper, "trapezpoid");
    ans = 5.95029;
    EXPECT_FLOAT_EQ(t.area(), ans); 
}

TEST_F(TestTrapezoid, TestPerimetr) {
    Point left_lower(0.0, 0.0), right_lower(6.0, 0.0), left_upper(2.0, 2.0), right_upper(4.0, 2.0);
    t = Trapezoid(left_lower, right_lower, left_upper, right_upper, "trapezoid");
    double ans = 13.656855;
    EXPECT_FLOAT_EQ(t.perimetr(), ans);

    left_lower = Point(0.0, 0.0); right_lower = Point(4.0, 0.0); left_upper = Point(1.0, 2.0); right_upper = Point(4.0, 2.0);
    t = Trapezoid(left_lower, right_lower, left_upper, right_upper, "trapezpoid");
    ans = 11.236068;
    EXPECT_FLOAT_EQ(t.perimetr(), ans); 
}

TEST_F(TestTrapezoid, TestCenter) {
    Point left_lower(0.0, 0.0), right_lower(6.0, 0.0), left_upper(2.0, 2.0), right_upper(4.0, 2.0);
    t = Trapezoid(left_lower, right_lower, left_upper, right_upper, "trapezoid");
    Point ans = Point(3.0, 1.0);
    EXPECT_EQ(t.center(), ans);

    left_lower = Point(0.0, 0.0); right_lower = Point(4.0, 0.0); left_upper = Point(1.0, 2.0); right_upper = Point(4.0, 2.0);
    t = Trapezoid(left_lower, right_lower, left_upper, right_upper, "trapezpoid");
    ans = Point(2.25, 1.0);
    EXPECT_EQ(t.center(), ans);
}

TEST_F(TestTrapezoid, TestOperatorEqual) {
    Point left_lower(0.0, 0.0), right_lower(6.0, 0.0), left_upper(2.0, 2.0), right_upper(4.0, 2.0);
    t = Trapezoid(left_lower, right_lower, left_upper, right_upper, "trapezoid");
    Trapezoid t2 = Trapezoid(left_lower, right_lower, left_upper, right_upper, "Trapezoid2");
    ASSERT_TRUE(t == t2);
    left_lower = Point(0.0, 0.0); right_lower = Point(4.0, 0.0); left_upper = Point(1.0, 2.0); right_upper = Point(4.0, 2.0);
    t2 = Trapezoid(left_lower, right_lower, left_upper, right_upper, "trap");
    ASSERT_FALSE(t == t2);
}

TEST_F(TestTrapezoid, TestOperatorNotEqual) {
    Point left_lower(0.0, 0.0), right_lower(6.0, 0.0), left_upper(2.0, 2.0), right_upper(4.0, 2.0);
    t = Trapezoid(left_lower, right_lower, left_upper, right_upper, "trapezoid");
    Trapezoid t2 = Trapezoid(left_lower, right_lower, left_upper, right_upper, "Trapezoid2");
    ASSERT_FALSE(t != t2);
    left_lower = Point(0.0, 0.0); right_lower = Point(4.0, 0.0); left_upper = Point(1.0, 2.0); right_upper = Point(4.0, 2.0);
    t2 = Trapezoid(left_lower, right_lower, left_upper, right_upper, "trap");
    ASSERT_TRUE(t != t2);
}

TEST_F(TestTrapezoid, TestOperatorDouble) {
    Point left_lower(0.0, 0.0), right_lower(6.0, 0.0), left_upper(2.0, 2.0), right_upper(4.0, 2.0);
    t = Trapezoid(left_lower, right_lower, left_upper, right_upper, "trapezoid");
    double ans = 10.338387;
    EXPECT_FLOAT_EQ(static_cast<double>(t), ans);

    left_lower = Point(0.0, 0.0); right_lower = Point(4.0, 0.0); left_upper = Point(1.0, 2.0); right_upper = Point(4.0, 2.0);
    t = Trapezoid(left_lower, right_lower, left_upper, right_upper, "trapezpoid");
    ans = 5.95029;
    EXPECT_FLOAT_EQ(static_cast<double>(t), ans); 
}

class TestPentagone: public testing::Test {

  protected:
  void SetUp() override {
    p = Pentagone();
  }

  void TearDown() override {
    p.~Pentagone();
  }

  Pentagone p;
};

TEST_F(TestPentagone, TestArea) {
    Point left_lower(0.0, 1.0), right_lower(0.951, 0.309), left_middle(0.588, -0.809), right_middle(-0.588, -0.809), upper(-0.951, 0.309);
    p = Pentagone(left_lower, right_lower, left_middle, right_middle, upper, "pent");

    double ans = 1.3140510000000001;
    EXPECT_FLOAT_EQ(p.area(), ans);

    left_lower = Point(1, 0); right_lower = Point(0.588, -0.809); left_middle = Point(-0.951, 0.309); right_middle = Point(0.951, 0.309); upper = Point(0, 1);
    p = Pentagone(left_lower, right_lower, left_middle, right_middle, upper, "pent");
    ans = 1.7350509999999999;
    EXPECT_FLOAT_EQ(p.area(), ans);
}

TEST_F(TestPentagone, TestPerimetr) {
    Point left_lower(0.0, 1.0), right_lower(0.951, 0.309), left_middle(0.588, -0.809), right_middle(-0.588, -0.809), upper(-0.951, 0.309);
    p = Pentagone(left_lower, right_lower, left_middle, right_middle, upper, "pent");

    double ans = 8.0575943;
    EXPECT_FLOAT_EQ(p.perimetr(), ans);

    left_lower = Point(1, 0); right_lower = Point(0.588, -0.809); left_middle = Point(-0.951, 0.309); right_middle = Point(0.951, 0.309); upper = Point(0, 1);
    p = Pentagone(left_lower, right_lower, left_middle, right_middle, upper, "pent");
    ans = 6.4097104;
    EXPECT_FLOAT_EQ(p.perimetr(), ans);
}

TEST_F(TestPentagone, TestCenter) {
    Point left_lower(0.0, 1.0), right_lower(0.951, 0.309), left_middle(0.588, -0.809), right_middle(-0.588, -0.809), upper(-0.951, 0.5);
    p = Pentagone(left_lower, right_lower, left_middle, right_middle, upper, "pent");

    Point ans(0.0, 0.0382);
    EXPECT_FLOAT_EQ(ans.x, p.center().x);
    EXPECT_FLOAT_EQ(ans.y, p.center().y);

    left_lower = Point(1, 0); right_lower = Point(0.588, -0.809); left_middle = Point(-0.951, 0.309); right_middle = Point(0.951, 0.309); upper = Point(0, 1);
    p = Pentagone(left_lower, right_lower, left_middle, right_middle, upper, "pent");
    ans = Point(0.3176, 0.1618);
    EXPECT_FLOAT_EQ(ans.x, p.center().x);
    EXPECT_FLOAT_EQ(ans.y, p.center().y);
}

TEST_F(TestPentagone, TestOperatorEqual) {
    Point left_lower(0.0, 1.0), right_lower(0.951, 0.309), left_middle(0.588, -0.809), right_middle(-0.588, -0.809), upper(-0.951, 0.309);
    p = Pentagone(left_lower, right_lower, left_middle, right_middle, upper, "pent");
    Pentagone p1 = Pentagone(left_lower, right_lower, left_middle, right_middle, upper, "p2");
    ASSERT_TRUE(p == p1);
    left_lower = Point(0.0, -1.0); right_lower = Point(0.951, -0.309); left_middle = Point(0.588, 0.809); right_middle = Point(-0.588, 0.809); upper = Point(-0.951, -0.309);
    p1 = Pentagone(left_lower, right_lower, left_middle, right_middle, upper, "pent");
    ASSERT_FALSE(p == p1);
}

TEST_F(TestPentagone, TestOperatorNotEqual) {
    Point left_lower(0.0, 1.0), right_lower(0.951, 0.309), left_middle(0.588, -0.809), right_middle(-0.588, -0.809), upper(-0.951, 0.309);
    p = Pentagone(left_lower, right_lower, left_middle, right_middle, upper, "pent");
    Pentagone p1 = Pentagone(left_lower, right_lower, left_middle, right_middle, upper, "p2");
    ASSERT_FALSE(p != p1);
    left_lower = Point(0.0, -1.0); right_lower = Point(0.951, -0.309); left_middle = Point(0.588, 0.809); right_middle = Point(-0.588, 0.809); upper = Point(-0.951, -0.309);
    p1 = Pentagone(left_lower, right_lower, left_middle, right_middle, upper, "pent");
    ASSERT_TRUE(p != p1);
}

TEST_F(TestPentagone, TestOperatorDouble) {
    Point left_lower(0.0, 1.0), right_lower(0.951, 0.309), left_middle(0.588, -0.809), right_middle(-0.588, -0.809), upper(-0.951, 0.309);
    p = Pentagone(left_lower, right_lower, left_middle, right_middle, upper, "pent");

    double ans = 1.3140510000000001;
    EXPECT_FLOAT_EQ(static_cast<double>(p), ans);

    left_lower = Point(1, 0); right_lower = Point(0.588, -0.809); left_middle = Point(-0.951, 0.309); right_middle = Point(0.951, 0.309); upper = Point(0, 1);
    p = Pentagone(left_lower, right_lower, left_middle, right_middle, upper, "pent");
    ans = 1.7350509999999999;
    EXPECT_FLOAT_EQ(static_cast<double>(p), ans);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}