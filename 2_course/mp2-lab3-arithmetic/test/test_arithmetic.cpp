// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"

TEST(arithmetic, check_operators_priority) {
	EXPECT_EQ(2, arithmetic::operators_priority('+'));
	EXPECT_EQ(2, arithmetic::operators_priority('-'));
	EXPECT_EQ(1, arithmetic::operators_priority('*'));
	EXPECT_EQ(1, arithmetic::operators_priority('/'));
}

TEST(arithmetic, check_delete_spaces) {

	arithmetic test("    1          +         3");
	EXPECT_EQ("1+3", test.delete_spaces());
}

TEST(arithmetic, check_constructor) {
	ASSERT_NO_THROW(arithmetic test("    1          +         3"));
}

TEST(arithmetic, check_is_dot) {
	ASSERT_TRUE(arithmetic::is_dot('.'));
	ASSERT_FALSE(arithmetic::is_dot('+'));
	ASSERT_FALSE(arithmetic::is_dot('/'));
	ASSERT_FALSE(arithmetic::is_dot('-'));
	ASSERT_FALSE(arithmetic::is_dot('*'));
}

TEST(arithmetic, check_is_digit) {
	ASSERT_TRUE(arithmetic::is_digit('4'));
	ASSERT_FALSE(arithmetic::is_digit('a'));
	ASSERT_FALSE(arithmetic::is_digit('+'));
	ASSERT_FALSE(arithmetic::is_digit('A'));
	ASSERT_FALSE(arithmetic::is_digit('!'));
}

TEST(arithmetic, check_convert) {
	arithmetic test("    1          +         3");
	EXPECT_EQ("1 3 + ", test.convert());
	arithmetic test_2("(1 + 2) /  3");
	EXPECT_EQ("1 2 + 3 / ", test_2.convert());
	arithmetic test_3("(2+6)");
	EXPECT_NE("+ 2 6", test_3.convert());
}

TEST(arithmetic, test_compute) {
	arithmetic test("    1          +         3");
	std::string expr_after_transforming = test.convert();
	EXPECT_EQ(4, test.compute(expr_after_transforming));
	arithmetic test_1("-11.3");
	std::string expr_after_transforming_1 = test_1.convert();
	EXPECT_EQ(-11.3, test_1.compute(expr_after_transforming_1));
	arithmetic test_2("(((1 + 1) * 1 + 1) * 1 + 1) + 1");
	std::string expr_after_transforming_2 = test_2.convert();
	ASSERT_NEAR(test_2.compute(expr_after_transforming_2), 5.0, 1e-15);
}


TEST(arithmetic, pause) {
	system("pause");
}