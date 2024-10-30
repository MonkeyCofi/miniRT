/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:49:13 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/30 10:13:22 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define MIN_T_DIFFERENCE 0.0001

// pass minirt here change everything according to paramters passed
t_cylinder	*create_cylinder(t_tuple orientation)
{
	t_cylinder	*cyl;

	cyl = ft_calloc(1, sizeof(t_cylinder));
	if (!cyl)
		return (NULL);
	cyl->point = return_tuple(0, 0, 0, POINT);
	cyl->radius = 1;
	cyl->material = create_default_material();
	cyl->type = CYLINDER;
	cyl->orientation = return_tuple(orientation.x, orientation.y, orientation.z, orientation.w);
	cyl->minimum = -INFINITY;
	cyl->maximum = INFINITY;
	cyl->is_closed = false;
	return (cyl);
}

t_tuple	normal_pos_cylinder(t_shape *shape, t_tuple pos)
{
	t_cylinder	*cylinder;
	double		distance;

	cylinder = shape->shape;
	distance = (pos.x * pos.x) + (pos.z * pos.z);
	if (distance < 1 && (pos.y >= cylinder->maximum - EPSILON)) // || is_equal(pos.y, cylinder->maximum - EPSILON)))
		return (return_vector(0, 1, 0));
	else if (distance < 1 && (pos.y <= cylinder->minimum + EPSILON)) // || is_equal(pos.y, cylinder->minimum + EPSILON)))
		return (return_vector(0, -1, 0));
	return (return_vector(pos.x, 0, pos.z));
}

static t_bool	at_cap(t_ray *ray, double radius, double t)
{
	double	x;
	double	z;
	
	x = ray->origin.x + t * ray->direction.x;
	z = ray->origin.z + t * ray->direction.z;
	// printf("at_cap: t = %f, x = %f, z = %f, radius = %f\n", t, x, z, 1.0);
	(void)radius;
	// in this if condition the numbers needa be changed w the max and min pls remember this
	 if ((x * x) + (z * z) <= 1 
	 && (ray->origin.y + t * ray->direction.y >= -1.0
	 && ray->origin.y + t * ray->direction.y <= 2.0))
		return true;
	return (false);
	// return ((x * x) + (z * z) <= radius * radius);
}

static t_bool	cylinder_end_hit(t_cylinder *cylinder, t_shape *shape_ptr, t_ray *ray, t_intersects *intersects)
{
	double	t;
	double	e = 0.01;
	if (cylinder->is_closed == 0)
		return (false);
	// canbe epsiolon
	if (fabs(ray->direction.y) > e)
	{
		if (ray->direction.y != 0)
		{
			t = (cylinder->minimum - ray->origin.y) / ray->direction.y;
			//  printf("Minimum cap: t = %f\n", t);
			if (t > 0 && at_cap(ray, t, cylinder->radius))
			{
				add_to_intersect(t, shape_ptr, intersects, CYLINDER, cylinder);
			}
			// intersections w teh max cap
			t = (cylinder->maximum - ray->origin.y) / ray->direction.y;
			// printf("Maximum cap: t = %f\n", t);
			if (t > 0 && t <= 2.0 && at_cap(ray, t, cylinder->radius)) {
				add_to_intersect(t, shape_ptr, intersects, CYLINDER, cylinder);
			}
		}
	}
	return	(true);
}

// 	{
// 		t = (cylinder->minimum - ray->origin.y) / ray->direction.y;
// 		if (at_cap(ray, t, cylinder->radius))
// 		{
// 			if (add_to_intersect(t, shape_ptr, intersects, CYLINDER, cylinder) == false)
// 				return (true);
// 		}
// 		t = (cylinder->maximum - ray->origin.y) / ray->direction.y;
// 		if (at_cap(ray, t, cylinder->radius))
// 			add_to_intersect(t, shape_ptr, intersects, CYLINDER, cylinder);
// 	}
// 	return (true);
// }




t_bool intersect_cylinder(t_minirt *m, t_intersects *intersects, t_ray *ray, int shape_index)
{
	t_cylinder	*cyl;
	double		a;
	double		b;
	double		c;
	double		disc;
	double		t[2];
	double		y[2];
	int			i;
	
	i = 0;
	cyl = m->shapes[shape_index]->shape; //
	a = (ray->direction.x * ray->direction.x) + (ray->direction.z * ray->direction.z);
	if (a < EPSILON)
		return (cylinder_end_hit(cyl, m->shapes[shape_index], ray, intersects));

	b = 2 * ray->origin.x * ray->direction.x + 2 * ray->origin.z * ray->direction.z;
	c = ray->origin.x * ray->origin.x + ray->origin.z * ray->origin.z - 1;
	disc = (b * b) - (4 * a * c);

	// for intersections with the body of the cylinder
	if (disc >= 0)
	{
		a *= 2;
		b = -b;
		disc = sqrt(disc);
		t[0] = (b - disc) / a;
		t[1] = (b + disc) / a;
		while (i < 2)
		{
			y[i] = ray->origin.y + t[i] * ray->direction.y;
			if (cyl->minimum < y[i] && y[i] < cyl->maximum)
				add_to_intersect(t[i], m->shapes[shape_index], intersects, CYLINDER, cyl);
			i++;
		}
	}
	// bottom cap
	if (ray->direction.y != 0 && cyl->is_closed)
	{
		double	t_bottom = (cyl->minimum - ray->origin.y) / ray->direction.y;
		if (t_bottom >= 0)
		{
			double	x = ray->origin.x + t_bottom * ray->direction.x;
			double	z = ray->origin.z + t_bottom * ray->direction.z;
			if (x * x + z * z <= 1)// we are in the cap btw replace 1 w radius
				add_to_intersect(t_bottom, m->shapes[shape_index], intersects, CYLINDER, cyl);
		}
	}
	// top cap
	if (ray->direction.y != 0 && cyl->is_closed)
	{
		double	t_top = (cyl->maximum - ray->origin.y) / ray->direction.y;
		if (t_top >= 0)
		{
			double	x = ray->origin.x + t_top * ray->direction.x;
			double	z = ray->origin.z + t_top * ray->direction.z;
			if (x * x + z * z <= 1)// we are in the cap btw replace 1 w radius
				add_to_intersect(t_top, m->shapes[shape_index], intersects, CYLINDER, cyl);
		}
	}
	//cylinder_end_hit(cyl, m->shapes[shape_index], ray, intersects);
	return (true);
}

// so to recap, in the version pierce had, the cylinder endd hit is called after checking for body
// intersections, which would in turn potentially make caps less precise, whereas in mine,
// the top and bottom caps are computed for separately, and the i call cyl end hit for more precisio.
// im so confused.. i have everything..
// i calculate t bottom as the intersection point along the y axis where the ray could hit bottom cap
// so using t_bottom i calculate x and z position of the ray..
// to confirm im within the radius of teh cap i have the if codition
// then i add it to intersects.. WTF AM I DOING WRONG
// im even calling cyl end hit at the end as im supposed to

// t_bool	intersect_cylinder(t_minirt *m, t_intersects *intersects, t_ray *ray, int shape_index)
// {
// 	t_cylinder	*cyl;
// 	double		a;
// 	double		b;
// 	double		c;
// 	double		disc;
// 	double		t[3];
// 	double		tt[2];
	
// 	cyl = m->shapes[shape_index]->shape;
// 	a = (ray->direction.x * ray->direction.x) + (ray->direction.z * ray->direction.z);
// 	if (a < EPSILON)
// 		return (cylinder_end_hit(cyl, m->shapes[shape_index], ray, intersects));
// 	b = 2 * ray->origin.x * ray->direction.x + 2 * ray->origin.z * ray->direction.z;
// 	c = ray->origin.x * ray->origin.x + ray->origin.z * ray->origin.z - 1;
// 	disc = (b * b) - (4 * a * c);
// 	if (disc < 0)
// 		return (false);
// 	a *= 2;
// 	b = -b;
// 	disc = sqrt(disc);
// 	t[0] = (b - disc) / (a);
// 	t[1] = (b + disc) / (a);
// 	//if (t[0] > t[1])
// 	//{
// 	//	t[2] = t[0];
// 	//	t[0] = t[1];
// 	//	t[1] = t[2];
// 	//}
// 	tt[0] = ray->origin.y + t[0] * ray->direction.y;
// 	if (cyl->minimum < tt[0] && tt[0] < cyl->maximum)
// 	{
// 		if (add_to_intersect(t[0], m->shapes[shape_index], intersects, CYLINDER, cyl) == false)
// 			return (true);
// 	}
// 	tt[1] = ray->origin.y + t[1] * ray->direction.y;
// 	if (cyl->minimum < tt[1] && tt[1] < cyl->maximum)
// 		add_to_intersect(t[1], m->shapes[shape_index], intersects, CYLINDER, cyl);
// 	cylinder_end_hit(cyl, m->shapes[shape_index], ray, intersects);
// 	return (true);
// }
