/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:06:55 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/23 21:49:47 by pipolint         ###   ########.fr       */
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

t_bool	is_in_shadow(t_minirt *minirt, t_tuple point, int light_index)
{
	t_intersection	*hit;
	t_intersects	*intersect;
	t_tuple			direction;
	t_tuple			new_point;
	t_ray			*ray;
	double			distance;
	
	new_point = subtract_tuples(&point, &minirt->lights[light_index]->position);
	direction = return_tuple(new_point.x, new_point.y, new_point.z, VECTOR);
	normalize(&direction);
	distance = magnitude(&new_point);
	ray = create_ray(new_point, direction);
	intersect = intersect_enivornment(minirt, ray, true);
	hit = best_hit(intersect);
	if (hit && hit->t < distance)
	{
		free(intersect);
		free(ray);
		return (true);
	}
	free(intersect);
	return (false);
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
		intersects->last_intersection = i;
		break ;
	}
	if (i == count && res == 0)
		return (NULL);
	return (res);
}

t_inter_comp	*precompute_intersect(t_intersects *inter, t_intersection *intersection, t_ray *ray)
{
	t_inter_comp	*new;
	t_ray			*object_ray;

	new = ft_calloc(1, sizeof(t_inter_comp));
	if (!new)
		return (NULL);
	new->intersects = inter;
	new->t = intersection->t;
	new->obj = intersection->shape_ptr;
	new->type = intersection->type;
	new->material = intersection->material;
	object_ray = create_ray(tuple_mult_fast(new->obj->inverse_mat, &ray->origin), tuple_mult_fast(new->obj->inverse_mat, &ray->direction));	// transformed into object space
	new->eye_vec = return_tuple(-ray->direction.x, -ray->direction.y, -ray->direction.z, VECTOR);	// eye vector in world space
	normalize(&new->eye_vec);
	new->point = position(ray, new->t);
	new->type = intersection->type;
	new->normal_vec = normal_at(new->obj, new->point);
	if (dot_product(&new->eye_vec, &new->normal_vec) < 0)
	{
		new->is_inside_object = true;
		negate(&new->normal_vec);
	}
	else
		new->is_inside_object = false;
	t_tuple test = return_scalar(&new->normal_vec, EPSILON);
	new->point_adjusted = add_vectors(&new->point, &test);
	return (new);
}

t_intersection	intersect(double t, t_shape_type type, void *shape, t_ray *ray, t_trans trans_type, t_tuple trans_coords, t_mater *material)
{
	t_intersection	intersection;
	t_ray			new_ray;

	if (trans_type != none)
		transform_ray(ray, trans_type, trans_coords, NULL);
	intersection.t = t;
	intersection.shape = shape;
	intersection.type = type;
	intersection.material = material;
	(void)new_ray;
	return (intersection);
}

t_intersects	*intersect_enivornment(t_minirt *minirt, t_ray *ray, t_bool shadow)
{
	t_intersects	*inter;
	t_ray			*real_ray;
	int				i;
	
	inter = ft_calloc(1, sizeof(t_intersects));
	i = -1;
	while (++i < minirt->object_count)
	{
		if (shadow == false)
			real_ray = create_ray(tuple_mult_fast(minirt->shapes[i]->inverse_mat, &ray->origin), tuple_mult_fast(minirt->shapes[i]->inverse_mat, &ray->direction));
		else
			real_ray = ray;
		if (minirt->shapes[i]->intersect(minirt, inter, real_ray, i) == false)
			continue ;
	}
	return (inter);
}

void	print_intersects(t_intersects *inter)
{
	for (int i = 0; i < inter->intersection_count; i++)
		printf("intersect[%d]: %f\n", i, inter->intersections[i].t);
}

t_tuple	position(t_ray *ray, double t)
{
	t_tuple	ret;

	set_point_points(&ret, \
		(ray->direction.x * t) + ray->origin.x, \
		(ray->direction.y * t) + ray->origin.y, \
		(ray->direction.z * t) + ray->origin.z);
	return (ret);
}

t_bool	add_to_intersect(double t, t_shape *shape_ptr, t_intersects *intersects, t_shape_type type, void *shape, t_mater *material)
{
	if (intersects->intersection_count < MAX_INTERSECTS)
	{
		intersects->intersections[intersects->intersection_count].t = t;
		intersects->intersections[intersects->intersection_count].type = type;
		intersects->intersections[intersects->intersection_count].shape = shape;
		intersects->intersections[intersects->intersection_count].material = material;
		intersects->intersections[intersects->intersection_count].shape_ptr = shape_ptr;
		if (intersects->intersection_count < MAX_INTERSECTS)
			intersects->intersection_count++;
		else
			return (false);
	}
	return (true);
}
