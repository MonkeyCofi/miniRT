/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:08:19 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/26 21:14:05 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	normal_at(t_shape *shape, t_tuple point)
{
	t_tuple	local_normal;
	t_tuple	point_obj_space;
	t_tuple	world_normal;

	point_obj_space = tuple_mult_fast(&shape->inverse_mat, &point);
	local_normal = shape->normal(shape, point_obj_space);
	world_normal = tuple_mult_fast(&shape->inverse_transpose, &local_normal);
	normalize(&world_normal);
	world_normal.w = VECTOR;
	return (world_normal);
}
