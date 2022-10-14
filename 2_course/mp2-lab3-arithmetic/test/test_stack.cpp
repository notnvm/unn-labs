// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(stack, create_stack_w_positive_size) {
	ASSERT_NO_THROW(stack<double> _stack(10));
}

TEST(stack, throw_when_create_stack_with_negative_size) {
	ASSERT_ANY_THROW(stack<double> _stack(-10));
}

TEST(stack, check_empty) {
	stack<double> _stack(10);
	EXPECT_EQ(true, _stack.empty());
}

TEST(stack, check_push) {
	stack<double> _stack(1);
	ASSERT_NO_THROW(_stack.push(1));
}

TEST(stack, check_clear) {
	stack<double> _stack(2);
	_stack.push(1);
	_stack.push(2);
	_stack.clear();
	EXPECT_EQ(true, _stack.empty());
}

TEST(stack, check_top) {
	stack<double> _stack(1);
	_stack.push(1);
	_stack.push(2);
	EXPECT_EQ(2, _stack.top());
}

TEST(stack, check_pop_) {
	stack<double> _stack(1);
	_stack.push(1);
	_stack.push(2);
	_stack.pop();
	EXPECT_EQ(1, _stack.top());
}

TEST(stack, throw_when_cant_pop) {
	stack<double> _stack(1);
	_stack.push(1);
	_stack.clear();
	ASSERT_ANY_THROW(_stack.pop());
}

TEST(stack, throw_when_cant_top) {
	stack<double> _stack(1);
	ASSERT_ANY_THROW(_stack.top());
}

TEST(stack, push_multiple_capacity) {
	stack<double> _stack(1);
	_stack.push(10); // size == 1; cap == 1;
	_stack.push(10); // size == 2; cap == 2;
	_stack.push(10); // size == 3; cap == 4;
	EXPECT_EQ(4, _stack.get_capacity());
}
