#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m1(2);
	for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) m1[i][j] = 1;
	TDynamicMatrix<int> m2(m1);

	EXPECT_EQ(1, m2[0][0]);
	EXPECT_EQ(1, m2[0][1]);
	EXPECT_EQ(1, m2[1][0]);
	EXPECT_EQ(1, m2[1][1]);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m1(2);
	for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) m1[i][j] = 1;
	TDynamicMatrix<int> m2(m1);

	EXPECT_NE(&m1[0], &m2[0]);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(5);
	EXPECT_EQ(5, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(4);
	m[0][0] = 4;
	EXPECT_EQ(4, m[0][0]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(4);

	ASSERT_ANY_THROW(m.at(-1, -1) = -1;);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(4);

	ASSERT_ANY_THROW(m.at(5, 0) = 5;);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(2);
	for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++)m[i][j] = 1;
	ASSERT_NO_THROW(m = m;);
	m = m;

	EXPECT_EQ(1, m[0][0]);
	EXPECT_EQ(1, m[0][1]);
	EXPECT_EQ(1, m[1][0]);
	EXPECT_EQ(1, m[1][1]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(2);
	for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++)m1[i][j] = 1;

	m2 = m1;

	EXPECT_EQ(1, m2[0][0]);
	EXPECT_EQ(1, m2[0][1]);
	EXPECT_EQ(1, m2[1][0]);
	EXPECT_EQ(1, m2[1][1]);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m1(2), m2(4);
	for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++)m1[i][j] = 1;

	m2 = m1;
	EXPECT_EQ(2, m2.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m1(2), m2(4);
	for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++)m1[i][j] = 1;

	m2 = m1;

	EXPECT_EQ(1, m2[0][0]);
	EXPECT_EQ(1, m2[0][1]);
	EXPECT_EQ(1, m2[1][0]);
	EXPECT_EQ(1, m2[1][1]);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m1(2), m2(2);
	for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++)m1[i][j] = m2[i][j] = 1;

	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(2);
	for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++)m[i][j] = 1;

	EXPECT_EQ(m, m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m1(2), m2(4);
	for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++)m1[i][j] = m2[i][j] = 1;

	EXPECT_NE(m1, m2);
}

TEST(TDynamicMatrix, can_multiply_scalar_to_matrix)
{
	TDynamicMatrix<int> m(2);
	for (int i = 0; i < 2; i++)for(int j = 0; j < 2; j++) m[i][j] = 1;
	m = m * 2;

	EXPECT_EQ(2, m[0][0]);
	EXPECT_EQ(2, m[0][1]);
	EXPECT_EQ(2, m[1][0]);
	EXPECT_EQ(2, m[1][1]);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(2), m;
	for (int i = 0; i < 2; i++)for (int j = 0; j < 2; j++) m1[i][j] = m2[i][j] = 1;
	m = m1 + m2;

	EXPECT_EQ(2, m[0][0]);
	EXPECT_EQ(2, m[0][1]);
	EXPECT_EQ(2, m[1][0]);
	EXPECT_EQ(2, m[1][1]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(4);
	for (int i = 0; i < 2; i++)for (int j = 0; j < 2; j++) m1[i][j] = m2[i][j] = 1;
	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(2), m;
	for (int i = 0; i < 2; i++)for (int j = 0; j < 2; j++) m1[i][j] = m2[i][j] = 1;
	m = m1 - m2;

	EXPECT_EQ(0, m[0][0]);
	EXPECT_EQ(0, m[0][1]);
	EXPECT_EQ(0, m[1][0]);
	EXPECT_EQ(0, m[1][1]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(4);
	for (int i = 0; i < 2; i++)for (int j = 0; j < 2; j++) m1[i][j] = m2[i][j] = 1;
	ASSERT_ANY_THROW(m1 - m2);
}

TEST(TDynamicMatrix, can_multiply_matrix_to_vector)
{
	TDynamicMatrix<int> m(2);
	TDynamicVector<int> v(2), res(2);
	for (int i = 0; i < 2; i++)for (int j = 0; j < 2; j++) m[i][j] = v[i] = 1;
	
	res = m * v;

	EXPECT_EQ(2, res[0]);
	EXPECT_EQ(2, res[1]);
}

TEST(TDynamicMatrix, cant_multiply_matrix_to_vector_with_not_equal_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicVector<int> v(4);
	for (int i = 0; i < 2; i++)for (int j = 0; j < 2; j++) m[i][j] = v[i] = 1;

	ASSERT_ANY_THROW(m * v);
}

TEST(TDynamicMatrix, can_multiply_matrix_to_matrix)
{
	TDynamicMatrix<int> m1(2),m2(2), m(2);

	for (int i = 0; i < 2; i++)for (int j = 0; j < 2; j++) m1[i][j] = m2[i][j] = 1;

	m = m1 * m2;

	EXPECT_EQ(2, m[0][0]);
	EXPECT_EQ(2, m[0][1]);
	EXPECT_EQ(2, m[1][0]);
	EXPECT_EQ(2, m[1][1]);
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(4);

	for (int i = 0; i < 2; i++)for (int j = 0; j < 2; j++) m1[i][j] = m2[i][j] = 1;

	ASSERT_ANY_THROW(m1 * m2);
}

