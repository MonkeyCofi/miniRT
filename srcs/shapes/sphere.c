/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:01:16 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/04 15:18:42 by ahaarij          ###   ########.fr       */
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

t_bool	sphere_hit(t_intersects *inter, t_ray *ray, t_shape *shape)
{
	t_disc		disc;
	t_sphere	*sphere;

	sphere = shape->shape;
	disc.shape = sphere;
	disc.a = dot_product(&ray->direction, &ray->direction);
	disc.b = 2 * dot_product(&ray->origin, &ray->direction);
	disc.c = dot_product(&ray->origin, &ray->origin) - (sphere->diameter);
	disc.disc = (disc.b * disc.b) - (4 * disc.a * disc.c);
	if (disc.disc < 0)
		return (false);
	disc.a *= 2;
	disc.b *= -1;
	disc.disc = sqrt(disc.disc);
	if (add_to_intersect((disc.b - disc.disc) / \
		(disc.a), shape, inter) == false)
		return (true);
	if (add_to_intersect((disc.b + disc.disc) / \
		(disc.a), shape, inter) == false)
		return (true);
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

void	init_sphere(t_minirt *m, int *i)
{
	t_sphere	*sphere;
	t_shape		*parsed;

	sphere = create_sphere(m, m->shapes[*i]->r);
	parsed = m->shapes[*i];
	m->shapes[*i] = create_shape(m, SPHERE, sphere);
	m->shapes[*i]->material = parsed->material;
	if (m->shapes[*i]->material->is_patterned == true)
		create_pattern(parsed->material->pattern.color_one,
			parsed->material->pattern.color_two,
			10, &parsed->material->pattern);
	m->shapes[*i]->transform = identity();
	m->shapes[*i]->coords = parsed->coords;
		transform_shape(m->shapes[*i], translate, 0);
	*i += 1;
}
