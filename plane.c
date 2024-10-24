/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:40:35 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/24 15:37:12 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_plane	*create_plane()
{
	t_plane	*plane;

	plane = ft_calloc(1, sizeof(t_plane));
	if (plane == NULL)
		return (NULL);
	return (plane);
}

t_bool	intersect_plane(t_minirt *m, t_intersects *intersects, t_ray *ray, int shape_index)
{
	if (fabs(ray->direction.y) < EPSILON)
		return (false);
	add_to_intersect(-ray->origin.y / ray->direction.y, m->shapes[shape_index], intersects, PLANE, m->shapes[shape_index]->shape, m->shapes[shape_index]->material);
	return (true);
}

t_tuple	*normal_pos_plane(t_shape *object, t_tuple point)
{
	// t_plane	*plane;
	t_tuple	*plane_normal;
	t_tuple	*world_normal;

	// plane = object->shape;
	plane_normal = ft_calloc(1, sizeof(t_tuple));
	plane_normal->x = 0;
	plane_normal->y = 1;
	plane_normal->z = 0;
	plane_normal->w = 0;
	(void)point;
	(void)object;
	(void)world_normal;
	return (plane_normal);
	//world_normal = tuple_mult(object->inverse_transpose, plane_normal);
	//world_normal->w = 0;
	//normalize(world_normal);
	//(void)point;
	//return (world_normal);
}
