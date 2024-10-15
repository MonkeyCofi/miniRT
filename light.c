/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:18:08 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/14 14:32:37 by pipolint         ###   ########.fr       */
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
t_tuple	lighting(t_mater *material, t_light *light, t_tuple point, t_tuple eye_vector, t_tuple normal_vector, t_bool in_shadow)
{
	t_tuple	final_color;
	t_tuple	light_vector;
	t_tuple	ambient;
	t_tuple	specular;
	t_tuple	diffuse;
	t_tuple	reflect_vector;
	float	light_dot;
	float	eye_dot;

	final_color = multiply_tuples(&light->intensity.colors, &material->color.colors, COLOR);
	light_vector = subtract_tuples(&point, &light->position);
	normalize(&light_vector);
	ambient = return_scalar(&final_color, material->ambient);
	light_dot = dot_product(&normal_vector, &light_vector);
	if (light_dot < 0)
	{
		diffuse = return_tuple(0, 0, 0, COLOR);
		specular = return_tuple(0, 0, 0, COLOR);
	}
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
			float fac = pow(eye_dot, material->shine);
			specular = return_scalar(&light->intensity.colors, material->specular * fac);
		}
	}
	if (in_shadow == true)
	{
		diffuse = return_tuple(0, 0, 0, COLOR);
		specular = return_tuple(0, 0, 0, COLOR);
	}
	return (return_tuple(diffuse.x + specular.x + ambient.x, diffuse.y + specular.y + ambient.y, diffuse.z + specular.z + ambient.z, COLOR));
}

t_light	create_light(t_tuple intensity, t_tuple position)
{
	t_light	light;

	light.intensity.colors = intensity;
	light.position = position;
	return (light);	
}

t_tuple	get_reflected_ray(t_tuple *from, t_tuple *normal)
{
	// reflection formula: 𝑟=𝑑−2(𝑑⋅𝑛)𝑛
	// from - 2 * dot_product(from, normal) * normal;
	float	dot;
	float	prod;
	t_tuple	_scalar;

	dot = dot_product(from, normal);
	prod = 2 * dot;
	_scalar = return_scalar(normal, prod);
	return (subtract_tuples(&_scalar, from));
}
