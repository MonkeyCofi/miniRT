/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:40:35 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/30 11:18:25 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_plane	*create_plane(t_minirt *m)
{
	t_plane	*plane;

	plane = calloc_and_check(sizeof(t_plane), 1, m, PL_ERR);
	return (plane);
}

t_bool	intersect_plane(t_intersects *intersects, t_ray *ray, t_shape *shape)
{
	if (fabs(ray->direction.y) < EPSILON)
		return (false);
	add_to_intersect(-ray->origin.y / ray->direction.y, shape, intersects);
	return (true);
}

t_tuple	normal_pos_plane(t_shape *object, t_tuple point)
{
	(void)object;
	(void)point;
	return (return_vector(0, 1, 0));
}
