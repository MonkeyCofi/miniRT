/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_cmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:59:11 by pipolint          #+#    #+#             */
/*   Updated: 2024/09/28 14:26:04 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bool	mat2d_cmp(t_2dmat *mat_one, t_2dmat *mat_two)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 2)
	{
		j = -1;
		while (++j < 2)
		{
			if (!is_equal(mat_one->matrix[i][j], mat_two->matrix[i][j]))
				return (false);
		}
	}
	return (true);
}

t_bool	mat3d_cmp(t_3dmat *mat_one, t_3dmat *mat_two)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			if (!is_equal(mat_one->matrix[i][j], mat_two->matrix[i][j]))
				return (false);
		}
	}
	return (true);
}

t_bool	mat4d_cmp(t_4dmat *mat_one, t_4dmat *mat_two)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (!is_equal(mat_one->matrix[i][j], mat_two->matrix[i][j]))
				return (false);
		}
	}
	return (true);
}