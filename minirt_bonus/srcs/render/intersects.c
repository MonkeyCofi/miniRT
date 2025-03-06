/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:06:55 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/10 19:00:03 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	sort_intersects(t_intersects *intersects)
{
	int				i;
	int				j;
	int				count;
	t_intersection	temp;

	i = 0;
	if (intersects->intersection_count < MAX_INTERSECTS)
		count = intersects->intersection_count;
	else
		count = MAX_INTERSECTS;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if (intersects->intersections[i].t > intersects->intersections[j].t)
			{
				temp = intersects->intersections[i];
				intersects->intersections[i] = intersects->intersections[j];
				intersects->intersections[j] = temp;
			}
			j++;
		}
		i++;
	}
}

t_intersection	*best_hit(t_intersects *intersects)
{
	int				i;
	int				count;
	t_intersection	*res;

	i = -1;
	res = NULL;
	sort_intersects(intersects);
	if (intersects->intersection_count < MAX_INTERSECTS)
		count = intersects->intersection_count;
	else
		count = MAX_INTERSECTS;
	while (++i < count)
	{
		if (intersects->intersections[i].t < 0)
			continue ;
		res = &intersects->intersections[i];
		break ;
	}
	if (i == count && res == 0)
		return (NULL);
	return (res);
}

t_inter_comp	precompute_intersect(t_minirt *minirt, t_intersects *inter, \
t_intersection *intersection, t_ray *ray)
{
	t_inter_comp	new;
	t_tuple			point_adjusted;

	new.intersects = inter;
	new.t = intersection->t;
	new.obj = intersection->shape_ptr;
	new.type = intersection->type;
	new.material = intersection->material;
	new.point = position(ray, new.t);
	new.type = intersection->type;
	new.eye_vec = return_vector(-ray->direction.x, \
		-ray->direction.y, -ray->direction.z);
	normalize(&new.eye_vec);
	new.normal_vec = normal_at(new.obj, new.point);
	new.is_inside_object = false;
	if (dot_product(&new.eye_vec, &new.normal_vec) < 0)
	{
		new.is_inside_object = true;
		negate(&new.normal_vec);
	}
	new.m = minirt;
	point_adjusted = return_point(new.normal_vec.x * EPSILON, \
		new.normal_vec.y * EPSILON, new.normal_vec.z * EPSILON);
	new.point_adjusted = add_vectors(&new.point, &point_adjusted);
	return (new);
}

t_intersection	intersect(double t, t_shape_type type, \
	void *shape, t_mater *material)
{
	t_intersection	intersection;

	intersection.t = t;
	intersection.shape = shape;
	intersection.type = type;
	intersection.material = material;
	return (intersection);
}

t_intersects	intersect_enivornment(t_minirt *minirt, t_ray *ray)
{
	t_intersects	inter;
	t_ray			ray_world_space;
	int				i;

	i = -1;
	inter.intersection_count = 0;
	while (++i < minirt->object_count)
	{
		ray_world_space = create_ray_static(tuple_mult(\
			&minirt->shapes[i]->inverse_mat, &ray->origin), \
			tuple_mult(&minirt->shapes[i]->inverse_mat, &ray->direction));
		if (minirt->shapes[i]->intersect(&inter, \
			&ray_world_space, minirt->shapes[i]) == false)
			continue ;
	}
	return (inter);
}
