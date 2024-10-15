/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:49:13 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/14 19:16:16 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cylinder	*create_cylinder(t_tuple orientation)
{
	t_cylinder	*cyl;

	cyl = ft_calloc(1, sizeof(t_cylinder));
	if (!cyl)
		return (NULL);
	cyl->transform = identity();
	cyl->point = return_tuple(0, 0, 0, POINT);
	cyl->inverse = NULL;
	cyl->material = create_default_material();
	cyl->type = CYLINDER;
	cyl->orientation = return_tuple(orientation.x, orientation.y, orientation.z, orientation.w);
	return (cyl);
}

t_bool	cylinder_hit(t_minirt *m, t_intersects *intersects, t_ray *ray, t_cylinder *cyl)
{
	float	a;
	float	b;
	float	c;
	float	disc;
	
	a = (ray->direction.x * ray->direction.x) + (ray->direction.z * ray->direction.z);
	if (is_equal(a, 0))
		return (false);
	b = (2 * (ray->origin.x * ray->origin.x)) + (2 * (ray->origin.z * ray->origin.z));
	c = (ray->origin.x * ray->origin.x) + (ray->origin.z * ray->origin.z) - 1;
	disc = (b * b) - 4 * a * c;
	if (disc < 0)
		return (false);
	if (intersects->intersection_count < MAX_INTERSECTS)
	{
		intersects->intersections[intersects->intersection_count].t = (-b - sqrt(disc)) / (2 * a);
		intersects->intersections[intersects->intersection_count].shape = cyl;
		intersects->intersections[intersects->intersection_count].type = CYLINDER;
		intersects->intersections[intersects->intersection_count].material = cyl->material;
		if (intersects->intersection_count < MAX_INTERSECTS)
			intersects->intersection_count++;
		else
			return (true);
	}
	if (intersects->intersection_count < MAX_INTERSECTS)
	{
		intersects->intersections[intersects->intersection_count].t = (-b + sqrt(disc)) / (2 * a);
		intersects->intersections[intersects->intersection_count].shape = cyl;
		intersects->intersections[intersects->intersection_count].type = CYLINDER;
		intersects->intersections[intersects->intersection_count].material = cyl->material;
		if (intersects->intersection_count < MAX_INTERSECTS)
			intersects->intersection_count++;
	}
	(void)m;
	return (true);
}
