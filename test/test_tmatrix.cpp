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
	TMatrix<int> a(5);
	for (int i = 0; i < 5; i++)
		for (int j = i; j < 5; ++j)
			a[i][j] = 5 * i + 2 * j;
	TMatrix<int> b(a);

	EXPECT_EQ(a, b);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	TMatrix<int> a(5);
	a[2][3] = -7;
	TMatrix<int> b(a);
	b[2][3] = 2;

	ASSERT_TRUE(a[2][3] != b[2][3]);
}

TEST(TMatrix, can_get_size)
{
	TMatrix<int> a(5);
	EXPECT_EQ(a.GetSize(), 5);
}

TEST(TMatrix, can_set_and_get_element)
{
	TMatrix<int> a(5);
	ASSERT_NO_THROW(a[3][4] = 7);
	EXPECT_EQ(a[3][4], 7);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	TMatrix<int> a(5);
	ASSERT_ANY_THROW(a[-2][4] = 7);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	TMatrix<int> a(5);
	ASSERT_ANY_THROW(a[3][9] = 7);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	TMatrix<int> a(5);
	ASSERT_NO_THROW(a = a);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	TMatrix<int> a(5);
	for (int i = 0; i < 5; i++)
		for (int j = i; j < 5; ++j)
			a[i][j] = 5 * i + 2 * j;

	TMatrix<int> b(5);
	ASSERT_NO_THROW(b = a);

	EXPECT_EQ(a, b);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	TMatrix<int> a(5);
	for (int i = 0; i < 5; i++)
		for (int j = i; j < 5; ++j)
			a[i][j] = 5 * i + 2 * j;

	TMatrix<int> b(3);
	ASSERT_NO_THROW(b = a);

	EXPECT_EQ(b.GetSize(), 5);
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	TMatrix<int> a(5);
	for (int i = 0; i < 5; i++)
		for (int j = i; j < 5; ++j)
			a[i][j] = 5 * i + 2 * j;

	TMatrix<int> b(3);
	ASSERT_NO_THROW(b = a);

	EXPECT_EQ(a, b);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	TMatrix<int> a(5);
	for (int i = 0; i < 5; i++)
		for (int j = i; j < 5; ++j)
			a[i][j] = 5 * i + 2 * j;
	TMatrix<int> b(a);

	ASSERT_TRUE(a == b);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	TMatrix<int> a(5);
	for (int i = 0; i < 5; i++)
		for (int j = i; j < 5; ++j)
			a[i][j] = 5 * i + 2 * j;

	ASSERT_TRUE(a == a);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	TMatrix<int> a(5), b(5);
	for (int i = 0; i < 5; i++)
		for (int j = i; j < 5; ++j) {
			a[i][j] = 5 * i + 2 * j;
			b[i][j] = 4 * i + j;
		}

	ASSERT_TRUE(a != b);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	TMatrix<int> a(5), b(5), c(5);
	for (int i = 0; i < 5; i++)
		for (int j = i; j < 5; ++j) {
			a[i][j] = 5 * i + 2 * j;
			b[i][j] = 4 * i + j;
			c[i][j] = a[i][j] + b[i][j];
		}

	TMatrix<int> d(5);
	d = a + b;
	ASSERT_NO_THROW(a + b);

	EXPECT_EQ(c, d);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix<int> a(5), b(3);
	for (int i = 0; i < 5; i++)
		for (int j = i; j < 5; ++j)
			a[i][j] = 5 * i + 2 * j;

	for (int i = 0; i < 3; i++)
		for (int j = i; j < 3; ++j)
			b[i][j] = 4 * i + j;

	ASSERT_ANY_THROW(a + b);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	TMatrix<int> a(5), b(5), c(5);
	for (int i = 0; i < 5; i++)
		for (int j = i; j < 5; ++j) {
			a[i][j] = 5 * i + 2 * j;
			b[i][j] = 4 * i + j;
			c[i][j] = a[i][j] - b[i][j];
		}

	TMatrix<int> d(5);
	d = a - b;
	ASSERT_NO_THROW(a - b);

	EXPECT_EQ(c, d);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix<int> a(5), b(3);
	for (int i = 0; i < 5; i++)
		for (int j = i; j < 5; ++j)
			a[i][j] = 5 * i + 2 * j;

	for (int i = 0; i < 3; i++)
		for (int j = i; j < 3; ++j)
			b[i][j] = 4 * i + j;

	ASSERT_ANY_THROW(a - b);
}

TEST(TMatrix, can_multiply_matrices_with_equal_size)
{
	TMatrix<int> a(3), b(3);
	a[0][0] = 1;	a[0][1] = 2;	a[0][2] = 3;
					a[1][1] = 4;	a[1][2] = 5;
									a[2][2] = 6;

	b[0][0] = 2;	b[0][1] = 1;	b[0][2] = -2;
					b[1][1] = 3;	b[1][2] = 4;
									b[2][2] = -1;

	TMatrix<int> c(3);

	c[0][0] = 2;	c[0][1] = 7;	c[0][2] = 3;
					c[1][1] = 12;	c[1][2] = 11;
									c[2][2] = -6;
	
	TMatrix<int> d(3);
	d = a * b;
	ASSERT_NO_THROW(a * b);

	std::cout << "\na:\n" << a << "\nb:\n" << b << "\na*b:\n" << d << "\n";
	EXPECT_EQ(c, d);
}

TEST(TMatrix, cant_multiply_matrices_with_not_equal_size)
{
	TMatrix<int> a(3), b(2);
	a[0][0] = 1;	a[0][1] = 2;	a[0][2] = 3;
					a[1][1] = 4;	a[1][2] = 5;
									a[2][2] = 6;

	b[0][0] = 2;	b[0][1] = 1;
					b[1][1] = 3;


	ASSERT_ANY_THROW(a * b);
}
