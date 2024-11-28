/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:02:04 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/25 19:12:40 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

void	set_vector_points(t_tuple *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
	v->w = 0;
}

void	set_point_points(t_tuple *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
	v->w = 1;
}

t_tuple	return_point(double x, double y, double z)
{
	t_tuple	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	ret.w = POINT;
	return (ret);
}

t_tuple	return_vector(double x, double y, double z)
{
	t_tuple	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	ret.w = VECTOR;
	return (ret);
}

t_tuple	*return_color(double r, double g, double b, t_tuple *ret)
{
	ret->r = r;
	ret->g = g;
	ret->b = b;
	ret->w = COLOR;
	return (ret);
}
