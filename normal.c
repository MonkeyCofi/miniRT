/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:08:19 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/21 21:04:19 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	normal_at(t_shape *shape, t_tuple point)
{
	t_tuple	local_point;
	t_tuple	*local_normal;
	t_tuple	world_normal;
	
	local_point = tuple_mult_fast(shape->inverse_mat, &point);
	local_normal = shape->normal(shape, point);
	world_normal = tuple_mult_fast(shape->inverse_transpose, local_normal);
	world_normal.w = 0;
	return (world_normal);
}
