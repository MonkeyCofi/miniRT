/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:49:13 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/15 18:23:19 by pipolint         ###   ########.fr       */
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
	cyl->is_closed = false;
	return (cyl);
}

t_bool	cap_present(t_ray *ray, float t)
{
	
}

t_bool	cylinder_hit(t_minirt *m, t_intersects *intersects, t_ray *ray, t_cylinder *cyl)
{
	float	a;
	float	b;
	float	c;
	float	disc;
	float	t[3];
	float	tt[2];
	
	a = (ray->direction.x * ray->direction.x) + (ray->direction.z * ray->direction.z);
	if (is_equal(a, 0))
		return (false);
	b = (2 * (ray->origin.x * ray->origin.x)) + (2 * (ray->origin.z * ray->origin.z));
	c = (ray->origin.x * ray->origin.x) + (ray->origin.z * ray->origin.z) - 1;
	disc = (b * b) - 4 * a * c;
	if (disc < 0)
		return (false);
	t[0] = (-b - sqrt(disc)) / (2 * a);
	t[1] = (-b - sqrt(disc)) / (2 * a);
	if (t[0] > t[1])
	{
		t[2] = t[0];
		t[0] = t[1];
		t[1] = t[2];
	}
	tt[0] = ray->origin.y + t[0] * ray->direction.y;
	if (tt[0] > cyl->minimum && tt[0] < cyl->maximum)
	{
		intersects->intersections[intersects->intersection_count].t = t[0];
		intersects->intersections[intersects->intersection_count].shape = cyl;
		intersects->intersections[intersects->intersection_count].type = CYLINDER;
		intersects->intersections[intersects->intersection_count].material = cyl->material;
		if (intersects->intersection_count < MAX_INTERSECTS)
			intersects->intersection_count++;
		else
			return (true);
	}
	tt[1] = ray->origin.y + t[1] * ray->direction.y;
	if (tt[1] > cyl->minimum && tt[1] < cyl->maximum)
	{
		intersects->intersections[intersects->intersection_count].t = t[1];
		intersects->intersections[intersects->intersection_count].shape = cyl;
		intersects->intersections[intersects->intersection_count].type = CYLINDER;
		intersects->intersections[intersects->intersection_count].material = cyl->material;
		if (intersects->intersection_count < MAX_INTERSECTS)
			intersects->intersection_count++;
	}
	(void)m;
	return (true);
}
