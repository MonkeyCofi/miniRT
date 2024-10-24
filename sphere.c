/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:01:16 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/24 18:01:48 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	*create_sphere(double originx, double originy, double originz, double radius, t_mater *material)
{
	t_sphere	*ret;

	ret = ft_calloc(1, sizeof(t_sphere));
	if (!ret)
		return (NULL);
	ret->center = return_tuple(originx, originy, originz, POINT);
	ret->color = return_tuple(0.8, 0.5, 0.3, 0);
	ret->radius = radius;
	ret->transform = identity();
	ret->current_inverse = NULL;
	ret->diameter = ret->radius * ret->radius;
	if (material)
		ret->material = create_material(material->color, material->diffuse, material->ambient, material->specular, material->shine);
	else
		ret->material = create_material(return_color(1, 1, 1), 0.9, 0.1, 0.9, 200);
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
	if (add_to_intersect((-vars[1] - sqrt(vars[3])) / (2 * vars[0]), minirt->shapes[shape_index], inter, SPHERE, sphere, sphere->material) == false)
		return (true);
	if (add_to_intersect((-vars[1] + sqrt(vars[3])) / (2 * vars[0]), minirt->shapes[shape_index], inter, SPHERE, sphere, sphere->material) == false)
		return (true);
	(void)minirt;
	return (true);
}

t_tuple	*normal_sphere(t_shape *shape, t_tuple pos)
{
	t_sphere	*sphere;
	t_tuple		temp;
	t_tuple		*normal;

	sphere = shape->shape;
	temp = subtract_tuples(&sphere->center, &pos);
	normal = return_tuple_pointer(temp.x, temp.y, temp.z, temp.w);
	return (normal);
}

t_tuple	*normal_sphere_test(t_shape *shape, t_tuple pos)
{
	t_sphere	*sphere;
	t_tuple		*res;

	sphere = shape->shape;
	res = ft_calloc(1, sizeof(t_tuple));
	res->x = pos.x - sphere->center.x;
	res->y = pos.y - sphere->center.y;
	res->z = pos.z - sphere->center.z;
	res->w = 0;
	normalize(res);
	return (res);
}
