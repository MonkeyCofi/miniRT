/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:02:04 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/01 20:48:51 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

void	set_vector_points(t_tuple *v, float x, float y, float z)
{
	v->x = x;
	v->y = y;
	v->z = z;
	v->w = 0;
}

void	set_point_points(t_tuple *v, float x, float y, float z)
{
	v->x = x;
	v->y = y;
	v->z = z;
	v->w = 1;
}

t_tuple	return_tuple(float x, float y, float z, float w)
{
	t_tuple	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	ret.w = w;
	return (ret);
}