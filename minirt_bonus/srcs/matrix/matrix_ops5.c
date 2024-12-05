/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:36:10 by ahaarij           #+#    #+#             */
/*   Updated: 2024/11/25 16:36:30 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_4dmat	mat4d_cross(t_4dmat *a, t_4dmat *b)
{
	t_4dmat	result;
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result.matrix[i][j] = a->matrix[i][j] - b->matrix[j][i];
			j++;
		}
		i++;
	}
	return (result);
}

t_tuple	tuple_mult_fast(t_4dmat *mat, t_tuple *tuple)
{
	t_tuple	resultant;

	resultant.x = (mat->m11 * tuple->x) + (mat->m12 * tuple->y) + \
	(mat->m13 * tuple->z) + (mat->m14 * tuple->w);
	resultant.z = (mat->m31 * tuple->x) + (mat->m32 * tuple->y) + \
	(mat->m33 * tuple->z) + (mat->m34 * tuple->w);
	resultant.y = (mat->m21 * tuple->x) + (mat->m22 * tuple->y) + \
	(mat->m23 * tuple->z) + (mat->m24 * tuple->w);
	resultant.w = (mat->m41 * tuple->x) + (mat->m42 * tuple->y) + \
	(mat->m33 * tuple->z) + (mat->m34 * tuple->w);
	return (resultant);
}
