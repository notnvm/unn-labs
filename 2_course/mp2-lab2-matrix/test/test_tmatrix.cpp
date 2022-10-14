#include "utmatrix.h"

#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix)
{
  TMatrix<int> m(5);

  ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
	TMatrix<int> source(5);
	TMatrix<int> copied(source);
	ASSERT_EQ(source, copied);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	TMatrix<int> source(3);
	TMatrix<int> copied(source);
	EXPECT_NE(&source[0], &copied[0]);
}

TEST(TMatrix, can_get_size)
{
	TMatrix<int> matrix(4);
	EXPECT_EQ(4, matrix.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
	TMatrix<int> matrix(4);
	matrix[0][0] = 10;
	EXPECT_EQ(matrix[0][0], 10);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	TMatrix<int> matrix(4);
	ASSERT_ANY_THROW(matrix[-1][0] = 10);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	TMatrix<int> matrix(4);
	ASSERT_ANY_THROW(matrix[7][0] = 10);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	TMatrix<int> matrix_1(3);
	TMatrix<int> matrix_2(3);
	matrix_1[0][0] = 10;
	matrix_2 = matrix_1;
	matrix_1 = matrix_1;
	EXPECT_EQ(matrix_2, matrix_1);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	TMatrix<int> matrix_1(3);
	TMatrix<int> matrix_2(3);
	matrix_1[0][0] = 10;
	matrix_2 = matrix_1;
	EXPECT_EQ(matrix_2, matrix_1);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	TMatrix<int> matrix_1(3);
	TMatrix<int> matrix_2(2);
	matrix_2 = matrix_1;
	EXPECT_EQ(3, matrix_2.GetSize());
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	TMatrix<int> matrix_1(3);
	TMatrix<int> matrix_2(2);
	matrix_2 = matrix_1;
	EXPECT_EQ(matrix_2, matrix_1);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	TMatrix<int> matrix_1(3);
	TMatrix<int> matrix_2(matrix_1);
	EXPECT_EQ(true, matrix_1 == matrix_2);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	TMatrix<int> matrix_1(3);
	EXPECT_EQ(true, matrix_1 == matrix_1);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	TMatrix<int> matrix_1(3);
	TMatrix<int> matrix_2(2);
	EXPECT_EQ(false, matrix_1 == matrix_2);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	TMatrix<int> matrix_1(3);
	TMatrix<int> matrix_2(3);
	TMatrix<int> matrix_result(3);
	matrix_1[0][0] = 1;
	matrix_2[0][0] = 4;
	matrix_result[0][0] = 5;
	EXPECT_EQ(matrix_result, matrix_1 + matrix_2);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix<int> matrix_1(3);
	TMatrix<int> matrix_2(2);
	ASSERT_ANY_THROW(matrix_1 + matrix_2);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	TMatrix<int> matrix_1(3);
	TMatrix<int> matrix_2(3);
	TMatrix<int> matrix_result(3);
	matrix_1[0][0] = 4;
	matrix_2[0][0] = 1;
	matrix_result[0][0] = 3; 
	EXPECT_EQ(matrix_result, matrix_1 - matrix_2);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix<int> matrix_1(3);
	TMatrix<int> matrix_2(2);
	ASSERT_ANY_THROW(matrix_1 - matrix_2);
}


