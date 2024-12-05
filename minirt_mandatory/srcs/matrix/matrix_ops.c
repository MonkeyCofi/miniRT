/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:03:16 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/25 16:36:05 by ahaarij          ###   ########.fr       */
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

t_4dmat	*mat4d_mult_fast_static2(t_4dmat *o, t_4dmat *t, t_4dmat *r)
{
	r->m31 = (o->m31 * t->m11) + (o->m32 * t->m21) + (o->m33 * t->m31) + \
	(o->m34 * t->m41);
	r->m32 = (o->m31 * t->m12) + (o->m32 * t->m22) + (o->m33 * t->m32) + \
	(o->m34 * t->m42);
	r->m33 = (o->m31 * t->m13) + (o->m32 * t->m23) + (o->m33 * t->m33) + \
	(o->m34 * t->m43);
	r->m34 = (o->m31 * t->m14) + (o->m32 * t->m24) + (o->m33 * t->m34) + \
	(o->m34 * t->m44);
	r->m41 = (o->m41 * t->m11) + (o->m42 * t->m21) + (o->m43 * t->m31) + \
	(o->m44 * t->m41);
	r->m42 = (o->m41 * t->m12) + (o->m42 * t->m22) + (o->m43 * t->m32) + \
	(o->m44 * t->m42);
	r->m43 = (o->m41 * t->m13) + (o->m42 * t->m23) + (o->m43 * t->m33) + \
	(o->m44 * t->m43);
	r->m44 = (o->m41 * t->m14) + (o->m42 * t->m24) + (o->m43 * t->m34) + \
	(o->m44 * t->m44);
	return (r);
}

t_4dmat	mat4d_mult_fast_static(t_4dmat *o, t_4dmat *t)
{
	t_4dmat	r;

	ft_bzero(&r, sizeof(t_4dmat));
	r.m11 = (o->m11 * t->m11) + (o->m12 * t->m21) + (o->m13 * t->m31) + \
	(o->m14 * t->m41);
	r.m12 = (o->m11 * t->m12) + (o->m12 * t->m22) + (o->m13 * t->m32) + \
	(o->m14 * t->m42);
	r.m13 = (o->m11 * t->m13) + (o->m12 * t->m23) + (o->m13 * t->m33) + \
	(o->m14 * t->m43);
	r.m14 = (o->m11 * t->m14) + (o->m12 * t->m24) + (o->m13 * t->m34) + \
	(o->m14 * t->m44);
	r.m21 = (o->m21 * t->m11) + (o->m22 * t->m21) + (o->m23 * t->m31) + \
	(o->m24 * t->m41);
	r.m22 = (o->m21 * t->m12) + (o->m22 * t->m22) + (o->m23 * t->m32) + \
	(o->m24 * t->m42);
	r.m23 = (o->m21 * t->m13) + (o->m22 * t->m23) + (o->m23 * t->m33) + \
	(o->m24 * t->m43);
	r.m24 = (o->m21 * t->m14) + (o->m22 * t->m24) + (o->m23 * t->m34) + \
	(o->m24 * t->m44);
	mat4d_mult_fast_static2(o, t, &r);
	return (r);
}
