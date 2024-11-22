/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:03:16 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/22 00:00:28 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_2dmat	*mat2d_mult(t_2dmat *mat_one, t_2dmat *mat_two)
{
	double	res[2][2];
	int		i;
	int		j;

	i = -1;
	while (++i < 2)
	{
		j = -1;
		while (++j < 2)
		{
			res[i][j] = mat_one->matrix[i][0] * mat_two->matrix[0][j] + \
						mat_one->matrix[i][1] * mat_two->matrix[1][j];
		}
	}
	return (create_2dmat(res));
}

t_3dmat	*mat3d_mult(t_3dmat *mat_one, t_3dmat *mat_two)
{
	double	res[3][3];
	int		i;
	int		j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			res[i][j] = mat_one->matrix[i][0] * mat_two->matrix[0][j] + \
						mat_one->matrix[i][1] * mat_two->matrix[1][j] + \
						mat_one->matrix[i][2] * mat_two->matrix[2][j];
		}
	}
	return (create_3dmat(res));
}

t_4dmat	*mat4d_mult(t_4dmat *mat_one, t_4dmat *mat_two)
{
	double	res[4][4];
	int		i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			res[i][j] = mat_one->matrix[i][0] * mat_two->matrix[0][j] + \
						mat_one->matrix[i][1] * mat_two->matrix[1][j] + \
						mat_one->matrix[i][2] * mat_two->matrix[2][j] + \
						mat_one->matrix[i][3] * mat_two->matrix[3][j];
		}
	}
	return (create_4dmat(res));
}

t_4dmat	*mat4d_mult_fast(t_4dmat *one, t_4dmat *two)
{
	t_4dmat	*res;
	
	res = ft_calloc(1, sizeof(t_4dmat));
	if (!res)
		return (NULL);
	res->m11 = (one->m11 * two->m11) + (one->m12 * two->m21) + (one->m13 * two->m31) + (one->m14 * two->m41);
	res->m12 = (one->m11 * two->m12) + (one->m12 * two->m22) + (one->m13 * two->m32) + (one->m14 * two->m42);
	res->m13 = (one->m11 * two->m13) + (one->m12 * two->m23) + (one->m13 * two->m33) + (one->m14 * two->m43);
	res->m14 = (one->m11 * two->m14) + (one->m12 * two->m24) + (one->m13 * two->m34) + (one->m14 * two->m44);
	
	res->m21 = (one->m21 * two->m11) + (one->m22 * two->m21) + (one->m23 * two->m31) + (one->m24 * two->m41);
	res->m22 = (one->m21 * two->m12) + (one->m22 * two->m22) + (one->m23 * two->m32) + (one->m24 * two->m42);
	res->m23 = (one->m21 * two->m13) + (one->m22 * two->m23) + (one->m23 * two->m33) + (one->m24 * two->m43);
	res->m24 = (one->m21 * two->m14) + (one->m22 * two->m24) + (one->m23 * two->m34) + (one->m24 * two->m44);
	
	res->m31 = (one->m31 * two->m11) + (one->m32 * two->m21) + (one->m33 * two->m31) + (one->m34 * two->m41);
	res->m32 = (one->m31 * two->m12) + (one->m32 * two->m22) + (one->m33 * two->m32) + (one->m34 * two->m42);
	res->m33 = (one->m31 * two->m13) + (one->m32 * two->m23) + (one->m33 * two->m33) + (one->m34 * two->m43);
	res->m34 = (one->m31 * two->m14) + (one->m32 * two->m24) + (one->m33 * two->m34) + (one->m34 * two->m44);
	
	res->m41 = (one->m41 * two->m11) + (one->m42 * two->m21) + (one->m43 * two->m31) + (one->m44 * two->m41);
	res->m42 = (one->m41 * two->m12) + (one->m42 * two->m22) + (one->m43 * two->m32) + (one->m44 * two->m42);
	res->m43 = (one->m41 * two->m13) + (one->m42 * two->m23) + (one->m43 * two->m33) + (one->m44 * two->m43);
	res->m44 = (one->m41 * two->m14) + (one->m42 * two->m24) + (one->m43 * two->m34) + (one->m44 * two->m44);
	
	return (res);
}

t_4dmat	mat4d_mult_fast_static(t_4dmat *one, t_4dmat *two)
{
	t_4dmat	res;
	
	ft_bzero(&res, sizeof(t_4dmat));
	res.m11 = (one->m11 * two->m11) + (one->m12 * two->m21) + (one->m13 * two->m31) + (one->m14 * two->m41);
	res.m12 = (one->m11 * two->m12) + (one->m12 * two->m22) + (one->m13 * two->m32) + (one->m14 * two->m42);
	res.m13 = (one->m11 * two->m13) + (one->m12 * two->m23) + (one->m13 * two->m33) + (one->m14 * two->m43);
	res.m14 = (one->m11 * two->m14) + (one->m12 * two->m24) + (one->m13 * two->m34) + (one->m14 * two->m44);
	
	res.m21 = (one->m21 * two->m11) + (one->m22 * two->m21) + (one->m23 * two->m31) + (one->m24 * two->m41);
	res.m22 = (one->m21 * two->m12) + (one->m22 * two->m22) + (one->m23 * two->m32) + (one->m24 * two->m42);
	res.m23 = (one->m21 * two->m13) + (one->m22 * two->m23) + (one->m23 * two->m33) + (one->m24 * two->m43);
	res.m24 = (one->m21 * two->m14) + (one->m22 * two->m24) + (one->m23 * two->m34) + (one->m24 * two->m44);
	
	res.m31 = (one->m31 * two->m11) + (one->m32 * two->m21) + (one->m33 * two->m31) + (one->m34 * two->m41);
	res.m32 = (one->m31 * two->m12) + (one->m32 * two->m22) + (one->m33 * two->m32) + (one->m34 * two->m42);
	res.m33 = (one->m31 * two->m13) + (one->m32 * two->m23) + (one->m33 * two->m33) + (one->m34 * two->m43);
	res.m34 = (one->m31 * two->m14) + (one->m32 * two->m24) + (one->m33 * two->m34) + (one->m34 * two->m44);
	
	res.m41 = (one->m41 * two->m11) + (one->m42 * two->m21) + (one->m43 * two->m31) + (one->m44 * two->m41);
	res.m42 = (one->m41 * two->m12) + (one->m42 * two->m22) + (one->m43 * two->m32) + (one->m44 * two->m42);
	res.m43 = (one->m41 * two->m13) + (one->m42 * two->m23) + (one->m43 * two->m33) + (one->m44 * two->m43);
	res.m44 = (one->m41 * two->m14) + (one->m42 * two->m24) + (one->m43 * two->m34) + (one->m44 * two->m44);

	return (res);
}

t_4dmat mat4d_cross(t_4dmat *a, t_4dmat *b)
{
    t_4dmat result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // Antisymmetric difference as a "cross-like" operation
            result.matrix[i][j] = a->matrix[i][j] - b->matrix[j][i];
        }
    }
    return result;
}

t_tuple	tuple_mult_fast(t_4dmat *mat, t_tuple *tuple)
{
	t_tuple	resultant;

	resultant.x = (mat->m11 * tuple->x) + (mat->m12 * tuple->y) + (mat->m13 * tuple->z) + (mat->m14 * tuple->w);
	resultant.y = (mat->m21 * tuple->x) + (mat->m22 * tuple->y) + (mat->m23 * tuple->z) + (mat->m24 * tuple->w);
	resultant.z = (mat->m31 * tuple->x) + (mat->m32 * tuple->y) + (mat->m33 * tuple->z) + (mat->m34 * tuple->w);
	resultant.w = (mat->m41 * tuple->x) + (mat->m42 * tuple->y) + (mat->m33 * tuple->z) + (mat->m34 * tuple->w);
	return (resultant);
}

t_tuple	*tuple_mult(t_4dmat *mat, t_tuple *tuple)
{
	t_tuple	*resultant;
	double	res[4];
	int		i;

	i = -1;
	while (++i < 4)
	{
		res[i] = mat->matrix[i][0] * tuple->x + \
				mat->matrix[i][1] * tuple->y + \
				mat->matrix[i][2] * tuple->z + \
				mat->matrix[i][3] * tuple->w;
	}
	resultant = ft_calloc(1, sizeof(t_tuple));
	resultant->x = res[0];
	resultant->y = res[1];
	resultant->z = res[2];
	resultant->w = res[3];
	return (resultant);
}

t_4dmat	identity()
{
	t_4dmat	matrix;

	ft_bzero(&matrix, sizeof(t_4dmat));
	matrix.m11 = 1;
	matrix.m22 = 1;
	matrix.m33 = 1;
	matrix.m44 = 1;
	return (matrix);
}

t_4dmat	transpose(t_4dmat *matrix)
{
	t_4dmat	matrix_transpose;

	matrix_transpose.matrix[0][0] = matrix->m11;
	matrix_transpose.matrix[0][1] = matrix->m21;
	matrix_transpose.matrix[0][2] = matrix->m31;
	matrix_transpose.matrix[0][3] = matrix->m41;
	matrix_transpose.matrix[1][0] = matrix->m12;
	matrix_transpose.matrix[1][1] = matrix->m22;
	matrix_transpose.matrix[1][2] = matrix->m32;
	matrix_transpose.matrix[1][3] = matrix->m42;
	matrix_transpose.matrix[2][0] = matrix->m13;
	matrix_transpose.matrix[2][1] = matrix->m23;
	matrix_transpose.matrix[2][2] = matrix->m33;
	matrix_transpose.matrix[2][3] = matrix->m43;
	matrix_transpose.matrix[3][0] = matrix->m14;
	matrix_transpose.matrix[3][1] = matrix->m24;
	matrix_transpose.matrix[3][2] = matrix->m34;
	matrix_transpose.matrix[3][3] = matrix->m44;
	return (matrix_transpose);
}

double	determinant(t_2dmat *mat_2d, t_3dmat *mat_3d, t_4dmat *mat_4d)
{
	double	(*cofact_3d)(t_3dmat *, int, int);
	double	(*cofact_4d)(t_4dmat *, int, int);

	cofact_3d = cofactor_3d;
	cofact_4d = cofactor_4d;
	if (mat_2d)
		return ((mat_2d->m11 * mat_2d->m22) - (mat_2d->m12 * mat_2d->m21));
	else if (mat_3d)
	{
		return ((mat_3d->m11 * cofact_3d(mat_3d, 0, 0)) + (mat_3d->m12 * cofact_3d(mat_3d, 0, 1)) + \
				(mat_3d->m13 * cofact_3d(mat_3d, 0, 2)));
	}
	else
	{
		return ((mat_4d->m11 * cofact_4d(mat_4d, 0, 0)) + (mat_4d->m12 * cofact_4d(mat_4d, 0, 1)) + (mat_4d->m13 * cofact_4d(mat_4d, 0, 2)) + \
				(mat_4d->m14 * cofact_4d(mat_4d, 0, 3)));
	}
}

t_2dmat	*submat_3d(t_3dmat *matrix, int row, int column)
{
	double	resultant[2][2];
	int		i;
	int		j;
	int		k;
	int		l;

	i = -1;
	k = 0;
	while (++i < 3)
	{
		if (i == row)
			continue ;
		j = -1;
		l = 0;
		while (++j < 3)
		{
			if (j == column)
				continue ;
			resultant[k][l++] = matrix->matrix[i][j];
		}
		k++;
	}
	return (create_2dmat(resultant));
}

t_3dmat	*submat_4d(t_4dmat *matrix, int row, int column)
{
	double	resultant[3][3];
	int		i;
	int		j;
	int		k;
	int		l;

	i = -1;
	k = 0;
	while (++i < 4)
	{
		if (i == row)
			continue ;
		j = -1;
		l = 0;
		while (++j < 4)
		{
			if (j == column)
				continue ;
			resultant[k][l++] = matrix->matrix[i][j];
		}
		k++;
	}
	return (create_3dmat(resultant));
}

double	minor_3d(t_3dmat *mat, int row, int column)
{
	t_2dmat	*submatrix;
	double	ret;

	submatrix = submat_3d(mat, row, column);
	ret = determinant(submatrix, NULL, NULL);
	free(submatrix);
	return (ret);
}

double	minor_4d(t_4dmat *mat, int row, int column)
{
	t_3dmat	*submatrix;
	double	ret;

	submatrix = submat_4d(mat, row, column);
	ret = determinant(NULL, submatrix ,NULL);
	free(submatrix);
	return (ret);
}

double	cofactor_3d(t_3dmat *mat, int row, int column)
{
	double	minor;
	double	cofact[3][3];
	
	minor = minor_3d(mat, row, column);
	cofact[0][0] = 1;
	cofact[0][1] = -1;
	cofact[0][2] = 1;
	cofact[1][0] = -1;
	cofact[1][1] = 1;
	cofact[1][2] = -1;
	cofact[2][0] = 1;
	cofact[2][1] = -1;
	cofact[2][2] = 1;
	return (minor * cofact[row][column]);
}

double	cofactor_4d(t_4dmat *mat, int row, int column)
{
	double	minor;
	double	cofact[4][4];
	
	minor = minor_4d(mat, row, column);
	cofact[0][0] = 1;
	cofact[0][1] = -1;
	cofact[0][2] = 1;
	cofact[0][3] = -1;
	cofact[1][0] = -1;
	cofact[1][1] = 1;
	cofact[1][2] = -1;
	cofact[1][3] = 1;
	cofact[2][0] = 1;
	cofact[2][1] = -1;
	cofact[2][2] = 1;
	cofact[2][3] = -1;
	cofact[3][0] = -1;
	cofact[3][1] = 1;
	cofact[3][2] = -1;
	cofact[3][3] = 1;
	return (minor * cofact[row][column]);
}

t_4dmat	*create_4dcofactor(t_4dmat *mat)
{
	double	res[4][4];
	double	(*cof)(t_4dmat *, int, int);
	int		i;
	int		j;

	i = -1;
	cof = cofactor_4d;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			res[i][j] = cof(mat, i, j);
	}
	return (create_4dmat(res));
}

t_bool	inverse_mat(t_4dmat *mat, t_4dmat **ptr)
{
	t_4dmat	*cofactor;
	t_4dmat	t;
	double	res[4][4];
	int		i;
	int		j;

	if (determinant(NULL, NULL, mat) == 0)
		return (false);
	cofactor = create_4dcofactor(mat);
	t = transpose(cofactor);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			res[i][j] = t.matrix[i][j] / determinant(NULL, NULL, mat);
	}
	free(cofactor);
	(*ptr) = create_4dmat(res);
	if (!ptr)
		return (error);
	return (true);
}

t_bool	inverse_mat_test(t_4dmat *mat, t_4dmat *ptr)
{
	t_4dmat	*cofactor;
	t_4dmat	t;
	double	deter;
	int		i;
	int		j;

	deter = determinant(NULL, NULL, mat);
	if (deter == 0)
		return (false);
	cofactor = create_4dcofactor(mat);
	t = transpose(cofactor);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			ptr->matrix[i][j] = t.matrix[i][j] / deter;
	}
	free(cofactor);
	return (true);
}

t_4dmat	axis_angle(t_tuple orientation, double angle)
{
	t_4dmat	matrix;
	double	cos_angle;

	normalize(&orientation);
	ft_bzero(&matrix, sizeof(t_4dmat));
	cos_angle = cos(angle);
	matrix.m11 = cos_angle + orientation.x * orientation.x * (1 - cos_angle);
	matrix.m12 = orientation.x * orientation.y * (1 - cos_angle) - orientation.z * sin(angle);
	matrix.m13 = orientation.x * orientation.z * (1 - cos_angle) + orientation.y * sin(angle);
	matrix.m21 = orientation.y * orientation.x * (1 - cos_angle) + orientation.z * sin(angle);
	matrix.m22 = cos_angle + orientation.y * orientation.y * (1 - cos_angle);
	matrix.m23 = orientation.y * orientation.z * (1 - cos_angle) - orientation.x * sin(angle);
	matrix.m31 =  orientation.z * orientation.x * (1 - cos_angle) - orientation.y * sin(angle);
	matrix.m32 = orientation.z * orientation.y * (1 - cos_angle) + orientation.x * sin(angle);
	matrix.m33 = cos_angle + orientation.z * orientation.z * (1 - cos_angle);
	matrix.m44 = 1;
	return (matrix);
}

void	copy_mat(t_4dmat *mat_one, t_4dmat *mat_two)
{
	mat_one->m11 = mat_two->m11;
	mat_one->m12 = mat_two->m12;
	mat_one->m13 = mat_two->m13;
	mat_one->m14 = mat_two->m14;
	mat_one->m21 = mat_two->m21;
	mat_one->m22 = mat_two->m22;
	mat_one->m23 = mat_two->m23;
	mat_one->m24 = mat_two->m24;
	mat_one->m31 = mat_two->m31;
	mat_one->m32 = mat_two->m32;
	mat_one->m33 = mat_two->m33;
	mat_one->m34 = mat_two->m34;
	mat_one->m41 = mat_two->m41;
	mat_one->m42 = mat_two->m42;
	mat_one->m43 = mat_two->m43;
	mat_one->m44 = mat_two->m44;
}
