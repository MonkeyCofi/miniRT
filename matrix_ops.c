/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:03:16 by pipolint          #+#    #+#             */
/*   Updated: 2024/09/28 19:59:31 by pipolint         ###   ########.fr       */
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
