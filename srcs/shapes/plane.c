/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:40:35 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/26 09:36:57 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_plane	*create_plane(t_minirt *m)
{
	t_plane	*plane;

	plane = calloc_and_check(sizeof(t_plane), 1, m, PL_ERR);
	return (plane);
}

t_bool	intersect_plane(t_minirt *m, t_intersects *intersects, t_ray *ray, \
int shape_index)
{
	if (fabs(ray->direction.y) < EPSILON)
		return (false);
	add_to_intersect(-ray->origin.y / ray->direction.y, \
	m->shapes[shape_index], intersects, PLANE, m->shapes[shape_index]->shape);
	return (true);
}

t_tuple	normal_pos_plane(t_shape *object, t_tuple point)
{
	(void)object;
	(void)point;
	return (return_vector(0, 1, 0));
}
