/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 21:06:40 by pipolint          #+#    #+#             */
/*   Updated: 2024/09/29 21:17:50 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	translate(t_tuple *point, float x, float y, float z)
{
	t_tuple	ret;
	t_4dmat	id;
	t_tuple	*res;

	id = identity();
	id.m14 = x;
	id.m24 = y;
	id.m34 = z;
	res = tuple_mult(&id, point);
	set_point_points(&ret, res->x, res->y, res->z);
	free(res);
	return (ret);
}