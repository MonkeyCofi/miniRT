/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:01:16 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/18 15:41:25 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	*create_sphere(float originx, float originy, float originz, t_mater *material)
{
	t_sphere	*ret;

	ret = ft_calloc(1, sizeof(t_sphere));
	if (!ret)
		return (NULL);
	ret->center = return_tuple(originx, originy, originz, POINT);
	ret->color = return_tuple(0.8, 0.5, 0.3, 0);
	ret->radius = 1;
	ret->transform = identity();
	ret->current_inverse = NULL;
	if (material)
		ret->material = create_material(material->color, material->diffuse, material->ambient, material->specular, material->shine);
	else
		ret->material = create_material(return_color(1, 1, 1, 1), 0.9, 0.1, 0.9, 200);
	return (ret);
}
t_bool	sphere_hit(t_minirt *minirt, t_camera *cam, t_intersects *inter, t_ray *ray, t_sphere *sphere, int with_transform, int i)
{
	float	vars[4];
	t_tuple	sphere_dist;
	t_4dmat	*inverse_ray_mat;
	t_ray	*inverse_ray;
	t_tuple	*res;

	inverse_ray_mat = NULL;
	if (!sphere)
		return (false);
	if (with_transform)
	{
		inverse_ray = create_ray(return_tuple(ray->origin.x, ray->origin.y, ray->origin.z, POINT), return_tuple(ray->direction.x, ray->direction.y, ray->direction.z, VECTOR));
		if (!sphere->current_inverse)
		{
			if (inverse_mat(&sphere->transform, &inverse_ray_mat) == error)
				return (error);
			if (!inverse_ray_mat)
				return (false);
			sphere->current_inverse = inverse_ray_mat;
			res = tuple_mult(inverse_ray_mat, &inverse_ray->origin);
			inverse_ray->origin = return_tuple(res->x, res->y, res->z, 1);
			res = tuple_mult(inverse_ray_mat, &inverse_ray->direction);
			inverse_ray->direction = return_tuple(res->x, res->y, res->z, 1);
		}
		else
		{
			res = tuple_mult(sphere->current_inverse, &inverse_ray->origin);
			inverse_ray->origin = return_tuple(res->x, res->y, res->z, 1);
			res = tuple_mult(sphere->current_inverse, &inverse_ray->direction);
			inverse_ray->direction = return_tuple(res->x, res->y, res->z, 1);
		}
		sphere_dist = subtract_tuples(&sphere->center, &inverse_ray->origin);
		vars[0] = dot_product(&inverse_ray->direction, &inverse_ray->direction);
		vars[1] = 2 * dot_product(&sphere_dist, &inverse_ray->direction);
	}
	else
	{
		sphere_dist = subtract_tuples(&sphere->center, &ray->origin);
		vars[0] = dot_product(&ray->direction, &ray->direction);
		vars[1] = 2 * dot_product(&sphere_dist, &ray->direction);
	}
	minirt->shapes[i]->inverse_mat = inverse_ray_mat;
	vars[2] = dot_product(&sphere_dist, &sphere_dist) - (sphere->radius * sphere->radius);
	vars[3] = (vars[1] * vars[1]) - (4 * vars[0] * vars[2]);
	if (vars[3] < 0)
		return (false);
	if (add_to_intersect((-vars[1] - sqrt(vars[3])) / (2 * vars[0]), inter, SPHERE, sphere, sphere->material) == false)
		return (true);
	if (add_to_intersect((-vars[1] + sqrt(vars[3])) / (2 * vars[0]), inter, SPHERE, sphere, sphere->material) == false)
		return (true);
	(void)cam;
	(void)minirt;
	return (true);
}

t_tuple	*normal_sphere(t_sphere *sphere, t_tuple pos)
{
	t_4dmat	*inverse_trans;
	t_tuple	*sphere_point;
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
			return (NULL);
		sphere->current_inverse = inverse_trans;
	}
	sphere_point = tuple_mult(sphere->current_inverse, &pos);
	sphere_norm = subtract_tuples(&sphere->center, sphere_point);
	world_norm = tuple_mult(transpose(inverse_trans), &sphere_norm);
	normalize(world_norm);
	world_norm->w = 0;
	return (world_norm);
}
