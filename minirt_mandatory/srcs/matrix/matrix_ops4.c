/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:35:27 by ahaarij           #+#    #+#             */
/*   Updated: 2024/11/25 16:36:33 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

t_4dmat	identity(void)
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
		return ((mat_3d->m11 * cofact_3d(mat_3d, 0, 0)) + \
				(mat_3d->m12 * cofact_3d(mat_3d, 0, 1)) + \
				(mat_3d->m13 * cofact_3d(mat_3d, 0, 2)));
	}
	else
	{
		return ((mat_4d->m11 * cofact_4d(mat_4d, 0, 0)) + \
				(mat_4d->m12 * cofact_4d(mat_4d, 0, 1)) + \
				(mat_4d->m13 * cofact_4d(mat_4d, 0, 2)) + \
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
