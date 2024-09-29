/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:03:16 by pipolint          #+#    #+#             */
/*   Updated: 2024/09/29 14:52:58 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_2dmat	*mat2d_mult(t_2dmat *mat_one, t_2dmat *mat_two)
{
	float	res[2][2];
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
	float	res[3][3];
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
	float	res[4][4];
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

t_tuple	*tuple_mult(t_4dmat *mat, t_tuple *tuple)
{
	t_tuple	*resultant;
	float	res[4];
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

t_4dmat	*transpose(t_4dmat *matrix)
{
	float	res[4][4];
	
	res[0][0] = matrix->m11;
	res[0][1] = matrix->m21;
	res[0][2] = matrix->m31;
	res[0][3] = matrix->m41;
	res[1][0] = matrix->m12;
	res[1][1] = matrix->m22;
	res[1][2] = matrix->m32;
	res[1][3] = matrix->m42;
	res[2][0] = matrix->m13;
	res[2][1] = matrix->m23;
	res[2][2] = matrix->m33;
	res[2][3] = matrix->m43;
	res[3][0] = matrix->m14;
	res[3][1] = matrix->m24;
	res[3][2] = matrix->m34;
	res[3][3] = matrix->m44;
	return (create_4dmat(res));
}

float	determinant(t_2dmat *mat)
{
	return ((mat->m11 * mat->m22) - (mat->m12 * mat->m21));
}

t_2dmat	*submat_3d(t_3dmat *matrix, int row, int column)
{
	float	resultant[2][2];
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
	float	resultant[3][3];
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
