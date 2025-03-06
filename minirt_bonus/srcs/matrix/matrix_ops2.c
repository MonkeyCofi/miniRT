/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:34:15 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/10 19:02:00 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

t_bool	inverse_mat(t_4dmat *mat, t_4dmat *ptr)
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
	matrix.m12 = orientation.x * orientation.y * (1 - cos_angle) - \
	orientation.z * sin(angle);
	matrix.m13 = orientation.x * orientation.z * (1 - cos_angle) + \
	orientation.y * sin(angle);
	matrix.m21 = orientation.y * orientation.x * (1 - cos_angle) + \
	orientation.z * sin(angle);
	matrix.m22 = cos_angle + orientation.y * orientation.y * (1 - cos_angle);
	matrix.m23 = orientation.y * orientation.z * (1 - cos_angle) - \
	orientation.x * sin(angle);
	matrix.m31 = orientation.z * orientation.x * (1 - cos_angle) - \
	orientation.y * sin(angle);
	matrix.m32 = orientation.z * orientation.y * (1 - cos_angle) + \
	orientation.x * sin(angle);
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
