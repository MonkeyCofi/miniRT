/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:18:08 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/29 22:05:11 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* 	Four components: ambient, diffuse, specular and shininess 
	ambient: light reflected from the background and other objects within the scene
	diffuse: reflection that is dependent on the light position and the object normal
	specular: the reflection of the light source
	shine: the ratio which signals how much shinier the specular reflection should be */
/* 	ambient: 
	diffuse: take the dot product of the surface normal and the light vector
	specular: take the dot product of the eye_vector and the light vector 
	shine: */
//t_tuple	lighting(t_shape *shape, t_mater *material, t_light *light, t_tuple point, t_tuple eye_vector, t_tuple normal_vector, t_bool in_shadow)
t_tuple	lighting(t_inter_comp *intersection, t_light *light, t_tuple point, t_tuple eye_vector, t_tuple normal_vector, t_bool in_shadow)
{
	t_tuple	final_color;
	t_tuple	light_vector;
	t_tuple	ambient;
	t_tuple	specular;
	t_tuple	diffuse;
	t_tuple	reflect_vector;
	t_tuple	color;
	t_mater	*material;
	double	light_dot;
	double	eye_dot;

	material = intersection->material;
	if (material->is_patterned == true)
	{
		if (intersection->type == CYLINDER)
		{
			double min_y = ((t_cylinder *)(intersection->obj->shape))->minimum;
			double max_y = ((t_cylinder *)(intersection->obj->shape))->maximum;

			// intersection point to object space
			t_tuple object_point = tuple_mult_fast(intersection->obj->inverse_mat, &intersection->point);
			double y_value = object_point.y;

			// if the intersection point is near the caps
			if (fabs(y_value - min_y) < EPSILON || fabs(y_value - max_y) < EPSILON)
			{
				// point is near the cap
				color = checkerboard_cap(material->pattern, object_point);
			}
			else
			{
				// point is on the cylindrical body
				color = checkerboard_cylinder(material->pattern, intersection);
			}
		}
		//color = pattern_at_point(material->pattern, point);
		else if (intersection->type == SPHERE)
		{
			//color = checkerboard_sphere(material->pattern, intersection);
			color = texture_sphere(intersection->point, intersection->ppm);
		}
		else
			//color = texture_plane(intersection->point, intersection->ppm);
			color = checkerboard(material->pattern, point);
	}
	else
		color = *material->color;
	//final_color = multiply_tuples(&light->intensity.colors, &material->color, COLOR);
	final_color = multiply_tuples(light->intensity, &color, COLOR);
	light_vector = subtract_tuples(&point, light->position);
	normalize(&light_vector);
	ambient = return_scalar(&final_color, material->ambient);
	light_dot = dot_product(&normal_vector, &light_vector);
	if (in_shadow || light_dot < 0)
		return (ambient);
	else
	{
		diffuse = return_scalar(&final_color, material->diffuse * light_dot);
		t_tuple negated_lightv = return_tuple(-light_vector.x, -light_vector.y, -light_vector.z, VECTOR);
		reflect_vector = get_reflected_ray(&negated_lightv, &normal_vector);
		eye_dot = dot_product(&reflect_vector, &eye_vector);
		if (eye_dot <= 0)
			specular = return_tuple(0, 0, 0, COLOR);
		else
		{
			double fac = pow(eye_dot, material->shine);
			specular = return_scalar(light->intensity, material->specular * fac);
		}
	}
	return (return_colorf(diffuse.x + specular.x + ambient.x, diffuse.y + specular.y + ambient.y, diffuse.z + specular.z + ambient.z));
}

t_light	create_light(t_tuple intensity, t_tuple position)
{
	t_light	light;

	light.intensity = &intensity;
	light.position = &position;
	return (light);	
}

t_tuple	get_reflected_ray(t_tuple *from, t_tuple *normal)
{
	// reflection formula: 𝑟=𝑑−2(𝑑⋅𝑛)𝑛
	// from - 2 * dot_product(from, normal) * normal;
	double	dot;
	double	prod;
	t_tuple	_scalar;

	dot = dot_product(from, normal);
	prod = 2 * dot;
	_scalar = return_scalar(normal, prod);
	return (subtract_tuples(&_scalar, from));
}
