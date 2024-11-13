/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:01:16 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/08 15:34:11 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	*create_sphere(t_minirt *m, double radius)
{
	t_sphere	*ret;

	ret = calloc_and_check(sizeof(t_sphere), 1, m, SPH_ERR);
	ret->center = return_point(0, 0, 0);
	ret->color = return_tuple(0.8, 0.5, 0.3, 0);
	ret->radius = radius;
	ret->diameter = ret->radius * ret->radius;
	return (ret);
}

t_bool	sphere_hit(t_minirt *minirt, t_intersects *inter, t_ray *ray, int shape_index)
{
	double		vars[4];
	t_sphere	*sphere;
	t_tuple		sphere_dist;

	sphere = minirt->shapes[shape_index]->shape;
	sphere_dist = subtract_tuples(&sphere->center, &ray->origin);
	vars[0] = dot_product(&ray->direction, &ray->direction);
	vars[1] = 2 * dot_product(&sphere_dist, &ray->direction);
	vars[2] = dot_product(&sphere_dist, &sphere_dist) - (sphere->diameter);
	vars[3] = (vars[1] * vars[1]) - (4 * vars[0] * vars[2]);
	if (vars[3] < 0)
		return (false);
	vars[0] *= 2;
	vars[1] *= -1;
	vars[3] = sqrt(vars[3]);
	if (add_to_intersect((vars[1] - vars[3]) / (vars[0]), minirt->shapes[shape_index], inter, SPHERE, sphere) == false)
		return (true);
	if (add_to_intersect((vars[1] + vars[3]) / (vars[0]), minirt->shapes[shape_index], inter, SPHERE, sphere) == false)
		return (true);
	(void)minirt;
	return (true);
}

t_tuple	normal_sphere(t_shape *shape, t_tuple pos)
{
	t_sphere	*sphere;
	t_tuple		temp;
	t_tuple		normal;

	sphere = shape->shape;
	temp = subtract_tuples(&sphere->center, &pos);
	normal = return_point(temp.x, temp.y, temp.z);
	return (normal);
}

