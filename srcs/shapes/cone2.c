/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:04:16 by ahaarij           #+#    #+#             */
/*   Updated: 2024/11/26 17:36:02 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// static void handle_cone_cap(t_minirt *m, t_intersects *intersects, t_ray *ray, t_cone *cone, double y_cap, int shape_index) {
//     double t, x, z, radius;

//     if (is_equal(ray->direction.y, 0)) return; // Skip if ray is parallel to cap

//     t = (y_cap - ray->origin.y) / ray->direction.y;
//     if (t < 0) return; // Skip if cap intersection is behind the ray

//     x = ray->origin.x + t * ray->direction.x;
//     z = ray->origin.z + t * ray->direction.z;
//     radius = (cone->maximum - y_cap) / (cone->maximum - cone->minimum);

//     if ((x * x) + (z * z) <= (radius * radius)) {
//         add_to_intersect(t, m->shapes[shape_index], intersects, CONE, cone);
//     }
// }

t_bool	pt2(t_norm_cone *s, t_minirt *m, t_intersects *intersects, t_ray *ray)
{
	int shape_index;

    shape_index = s->shape_index;
    s->disc = (s->b * s->b) - 4 * s->a * s->c;
    if (s->disc < 0)
        return (false);
    s->a *= 2;
    s->b *= -1;
    s->t[0] = (s->b - sqrt(s->disc)) / (s->a);
    s->t[1] = (s->b + sqrt(s->disc)) / (s->a);
    s->y[0] = ray->origin.y + s->t[0] * ray->direction.y;
    if (s->y[0] > s->cone->minimum && s->y[0] < s->cone->maximum)
    {
        if (add_to_intersect(s->t[0], m->shapes[shape_index], intersects, CONE, s->cone) == false)
            return (true);
    }
    s->y[1] = ray->origin.y + s->t[1] * ray->direction.y;
    if (s->y[1] > s->cone->minimum && s->y[1] < s->cone->maximum)
        add_to_intersect(s->t[1], m->shapes[shape_index], intersects, CONE, s->cone);
    // handle_cone_cap(m, intersects, ray, s->cone, s->cone->minimum, shape_index); // Bottom cap
    // handle_cone_cap(m, intersects, ray, s->cone, s->cone->maximum, shape_index); // Top cap
    return (true);
}

// t_bool	intersect_cone(t_minirt *m, t_intersects *intersects,
// 			t_ray *ray, int shape_index)
// {
// 	t_norm_cone	s;

// 	s.shape_index = shape_index;
// 	s.cone = m->shapes[shape_index]->shape;
// 	s.a = (ray->direction.x * ray->direction.x) - (ray->direction.y * \
// 	ray->direction.y) + (ray->direction.z * ray->direction.z);
// 	s.b = (2 * ray->origin.x * ray->direction.x) - (2 * ray->origin.y * \
// 	ray->direction.y) + (2 * ray->origin.z * ray->direction.z);
// 	s.c = (ray->origin.x * ray->origin.x) - (ray->origin.y * ray->origin.y) \
// 	+ (ray->origin.z * ray->origin.z);
// 	if (is_equal(s.a, 0))
// 	{
// 		if (is_equal(s.b, 0))
// 			return (false);
// 		if (add_to_intersect(-s.c / (2 * s.b), m->shapes[shape_index], \
// 		intersects, CONE, s.cone) == false)
// 			return (true);
// 	}
// 	if (pt2(&s, m, intersects, ray) == false)
// 		return (false);
// 	return (true);
// }


// void	bottom(t_minirt *m, t_intersects *intersects, \
// t_ray *ray, t_norm_cyl *s)
// {
// 	int		shape_index;
// 	double	t_bottom;
// 	double	x;
// 	double	z;

// 	shape_index = s->shape_index;
// 	if (ray->direction.y != 0 && s->cyl->is_closed)
// 	{
// 		t_bottom = (s->cyl->minimum - ray->origin.y) / ray->direction.y;
// 		if (t_bottom >= 0)
// 		{
// 			x = ray->origin.x + t_bottom * ray->direction.x;
// 			z = ray->origin.z + t_bottom * ray->direction.z;
// 			if (x * x + z * z <= s->cyl->radius)
// 				add_to_intersect(t_bottom, m->shapes[shape_index], \
// 				intersects, CYLINDER, s->cyl);
// 		}
// 	}
// }


t_bool intersect_cone(t_minirt *m, t_intersects *intersects, t_ray *ray, int shape_index)
{
    t_norm_cone s;

    s.shape_index = shape_index;
    s.cone = m->shapes[shape_index]->shape;
    s.a = (ray->direction.x * ray->direction.x) - (ray->direction.y * ray->direction.y) + (ray->direction.z * ray->direction.z);
    s.b = (2 * ray->origin.x * ray->direction.x) - (2 * ray->origin.y * ray->direction.y) + (2 * ray->origin.z * ray->direction.z);
    s.c = (ray->origin.x * ray->origin.x) - (ray->origin.y * ray->origin.y) + (ray->origin.z * ray->origin.z);

    if (is_equal(s.a, 0))
    {
        if (is_equal(s.b, 0))
            return (false);
        if (add_to_intersect(-s.c / (2 * s.b), m->shapes[shape_index], intersects, CONE, s.cone) == false)
            return (true);
    }
    if (pt2(&s, m, intersects, ray) == false)
        return (false);

    // Add cap intersections
    // handle_cone_cap(m, intersects, ray, s.cone, s.cone->minimum, shape_index); // Bottom cap
    // handle_cone_cap(m, intersects, ray, s.cone, s.cone->maximum, shape_index);

    return (true);
}