/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:06:55 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/14 21:05:29 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	*normal_pos_plane(t_plane *plane, t_tuple point);

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
	t_ray			*ray;
	t_intersects	*intersect;
	t_tuple			new_point;
	t_tuple			direction;
	float			distance;
	t_intersection	*hit;
	
	new_point = subtract_tuples(&point, &minirt->lights[light_index]->position);
	distance = magnitude(&new_point);
	direction = return_tuple(new_point.x, new_point.y, new_point.z, VECTOR);
	normalize(&direction);
	ray = create_ray(point, direction);
	intersect = intersect_enivornment(minirt, ray);
	hit = best_hit(intersect);
	if (hit && hit->t < distance)
	{
		free(intersect);	
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

	new = ft_calloc(1, sizeof(t_inter_comp));
	if (!new)
		return (NULL);
	new->eye_vec = return_tuple(-ray->direction.x, -ray->direction.y, -ray->direction.z, VECTOR);
	new->intersects = inter;
	new->t = intersection->t;
	new->obj = intersection->shape;
	new->type = intersection->type;
	new->material = intersection->material;
	//new->point = position(ray, inter->intersections[inter->intersection_count].t);
	new->point = position(ray, new->t);
	if (new->type == SPHERE)
		new->normal_vec = normal_pos(intersection->shape, new->point);
	else if (new->type == PLANE)
	{
		//printf("in here\n");
		new->normal_vec = normal_pos_plane(intersection->shape, new->point);
	}
	else if (new->type == CYLINDER)
	{
		new->normal_vec = normal_pos_cylinder(intersection->shape, new->point);
	}
	new->type = intersection->type;
	if (dot_product(&new->eye_vec, new->normal_vec) < 0)
	{
		new->is_inside_object = true;
		negate(new->normal_vec);
	}
	else
		new->is_inside_object = false;
	return (new);
}

//t_inter_comp	*precompute_intersect(t_intersects *inter, t_intersection *intersection, t_ray *ray, t_sphere *sphere)
//{
//	t_inter_comp	*new;

//	new = ft_calloc(1, sizeof(t_inter_comp));
//	if (!new)
//		return (NULL);
//	new->eye_vec = return_tuple(-ray->direction.x, -ray->direction.y, -ray->direction.z, VECTOR);
//	new->intersects = inter;
//	new->t = intersection->t;
//	//new->point = position(ray, inter->intersections[inter->intersection_count].t);
//	new->point = position(ray, new->t);
//	new->normal_vec = normal_pos(sphere, new->point);
//	new->obj = sphere;
//	if (dot_product(&new->eye_vec, new->normal_vec) < 0)
//	{
//		new->is_inside_object = true;
//		negate(new->normal_vec);
//	}
//	else
//		new->is_inside_object = false;
//	return (new);
//}

t_intersection	intersect(float t, t_shape_type type, void *shape, t_ray *ray, t_trans trans_type, t_tuple trans_coords, t_mater *material)
{
	t_intersection	intersection;
	t_ray			new_ray;

	if (trans_type != none)
		transform_ray(ray, trans_type, trans_coords, NULL);
	//else
	//	printf("Not transforming ray in intersect\n");
	intersection.t = t;
	intersection.shape = shape;
	intersection.type = type;
	intersection.material = material;
	(void)new_ray;
	return (intersection);
}

t_intersection	*intersect_plane(t_ray *ray, t_plane *plane)
{
	t_intersection	*plane_intersection;
	t_intersection	temp;

	if (fabs(ray->direction.y) < EPSILON)
		return (NULL);
	plane_intersection = ft_calloc(1, sizeof(t_intersection));
	temp = intersect(-ray->origin.y / ray->direction.y, PLANE, plane, ray, none, return_tuple(0, 0, 0, POINT), plane->material);
	plane_intersection->shape = temp.shape;
	plane_intersection->t = temp.t;
	plane_intersection->type = temp.type;
	plane_intersection->material = temp.material;
	return (plane_intersection);
}

t_intersects	*intersect_enivornment(t_minirt *minirt, t_ray *ray)
{
	t_intersects	*inter;
	int				i;
	
	inter = ft_calloc(1, sizeof(t_intersects));
	i = -1;
	while (++i < minirt->object_count)
	{
		if (minirt->shapes[i]->type == SPHERE)
		{
			if (sphere_hit(minirt, NULL, inter, ray, minirt->shapes[i]->shape, 1) == false)
				continue ;
		}
		else if (minirt->shapes[i]->type == PLANE)
		{
			if (inter->intersection_count < MAX_INTERSECTS)
			{
				t_intersection	*plane_intersect = intersect_plane(ray, minirt->shapes[i]->shape);
				if (plane_intersect)
				{
					inter->intersections[inter->intersection_count] = *plane_intersect;
					if (inter->intersection_count < MAX_INTERSECTS - 1)
						inter->intersection_count++;
					free(plane_intersect);
				}
			}
		}
		else if (minirt->shapes[i]->type == CYLINDER)
		{
			if (cylinder_hit(minirt, inter, ray, minirt->shapes[i]->shape) == false)
				continue ;
		}
	}
	return (inter);
}

void	print_intersects(t_intersects *inter)
{
	for (int i = 0; i < inter->intersection_count; i++)
		printf("intersect[%d]: %f\n", i, inter->intersections[i].t);
}

t_tuple	*normal_pos_plane(t_plane *plane, t_tuple point)
{
	t_tuple	*norml;

	norml = ft_calloc(1, sizeof(t_tuple));
	norml->x = plane->normal.x;
	norml->y = plane->normal.y;
	norml->z = plane->normal.z;
	norml->w = plane->normal.w;
	(void)point;
	return (norml);
	//t_4dmat	*inverse_trans;
	//t_tuple	*world_norm;
	//t_tuple	plane_norm;
	//t_bool	has_inverse;
	
	//if (plane->inverse)
	//	inverse_trans = plane->inverse;
	//else
	//{
	//	has_inverse = inverse_mat(&plane->transform, &inverse_trans);
	//	if (has_inverse == error)
	//		return (NULL);
	//	if (has_inverse == false)
	//	{
	//		printf("There is no inverse\n");
	//		return (NULL);
	//	}
	//	plane->inverse = inverse_trans;
	//	printf("assigned inverse to plane\n");
	//}
	//plane_norm = subtract_tuples(&plane->point, &point);
	//world_norm = tuple_mult(transpose(inverse_trans), &plane_norm);
	//world_norm->w = 0;
	//normalize(world_norm); 
	//return (world_norm);
	
	//function normal_at(shape, point)
	//local_point ← inverse(shape.transform) * point
	//local_normal ← local_normal_at(shape, local_point)
	//world_normal ← transpose(inverse(shape.transform)) * local_normal world_normal.w ← 0
	//return normalize(world_normal) end function
}

t_tuple	*normal_pos_cylinder(t_cylinder *cylinder, t_tuple pos)
{
	t_tuple		*normal;

	normal = ft_calloc(1, sizeof(t_tuple));
	normal->x = pos.x;
	normal->y = 0;
	normal->z = pos.z;
	normal->w = VECTOR;
	(void)cylinder;
	return (normal);
}

t_tuple	*normal_pos(t_sphere *sphere, t_tuple pos)
{
	t_4dmat	*inverse_trans;
	t_tuple	*world_norm;
	t_tuple	sphere_norm;
	t_bool	has_inverse;
	
	if (sphere->current_inverse)
		inverse_trans = sphere->current_inverse;
	else
	{
		has_inverse = inverse_mat(&sphere->transform, &inverse_trans);
		if (has_inverse == error)
			return (NULL);
		if (has_inverse == false)
		{
			printf("There is no inverse\n");
			return (NULL);
		}
		sphere->current_inverse = inverse_trans;
	}
	sphere_norm = subtract_tuples(&sphere->center, &pos);
	world_norm = tuple_mult(transpose(inverse_trans), &sphere_norm);
	normalize(world_norm);
	return (world_norm);
}

t_tuple	position(t_ray *ray, float t)
{
	t_tuple	ret;

	set_point_points(&ret, \
		(ray->direction.x * t) + ray->origin.x, \
		(ray->direction.y * t) + ray->origin.y, \
		(ray->direction.z * t) + ray->origin.z);
	return (ret);
}
