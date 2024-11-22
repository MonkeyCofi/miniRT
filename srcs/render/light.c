/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:18:08 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/22 14:22:32 by ahaarij          ###   ########.fr       */
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
// t_tuple	lighting(t_inter_comp *intersection, t_light *light, t_tuple point, t_tuple eye_vector, t_tuple normal_vector, t_bool in_shadow)
t_tuple	lighting(t_inter_comp *intersection, t_light *light, t_bool in_shadow)
{
	t_lighting	light_vars;
	double		eye_dot;

	light_vars.material = intersection->material;
	if (light_vars.material->is_patterned == true)
	{
		if (intersection->type == CYLINDER || intersection->type == CONE)
		{
			double min_y = ((t_cylinder *)(intersection->obj->shape))->minimum;
			double max_y = ((t_cylinder *)(intersection->obj->shape))->maximum;

			// intersection point to object space
			t_tuple object_point = tuple_mult_fast(&intersection->obj->inverse_mat, &intersection->point_adjusted);
			double y_value = object_point.y;

			// if the intersection point is near the caps
			if (fabs(y_value - min_y) < EPSILON || fabs(y_value - max_y) < EPSILON)
			{
				// point is near the cap
				light_vars.color = checkerboard_cap(light_vars.material->pattern, object_point);
			}
			else
			{
				// point is on the cylindrical body
				light_vars.color = checkerboard_cylinder(light_vars.material->pattern, intersection);
			}
		}
		//light_vars.color = pattern_at_point(light_vars.material->pattern, point);
		else if (intersection->type == SPHERE)
		{
			light_vars.color = checkerboard_sphere(light_vars.material->pattern, intersection);
			// light_vars.color = texture_sphere(intersection, intersection->ppm);
		}
		else
			//light_vars.color = texture_plane(intersection, intersection->ppm);
			light_vars.color = checkerboard(light_vars.material->pattern, intersection->point);
	}
	else
		light_vars.color = light_vars.material->color;
	//light_vars.final_color = multiply_tuples(&light->intensity, &light_vars.material->light_vars.color, COLOR);
	light_vars.final_color = multiply_tuples(&light->intensity, &light_vars.color, COLOR);
	light_vars.final_color = return_scalar(&light_vars.final_color, light->brightness);
	light_vars.light_vector = subtract_tuples(&intersection->point_adjusted, &light->position);
	normalize(&light_vars.light_vector);
	light_vars.ambient = return_scalar(&light_vars.final_color, light_vars.material->ambient);
	light_vars.light_dot = dot_product(&intersection->normal_vec, &light_vars.light_vector);
	if (in_shadow || light_vars.light_dot < 0)
		return (light_vars.ambient);
	else
	{
		light_vars.diffuse = return_scalar(&light_vars.final_color, light_vars.material->diffuse * light_vars.light_dot);
		light_vars.vec_to_light = return_tuple(-light_vars.light_vector.x, -light_vars.light_vector.y, -light_vars.light_vector.z, VECTOR);
		light_vars.reflect_vector = get_reflected_ray(&light_vars.vec_to_light, &intersection->normal_vec);
		eye_dot = dot_product(&light_vars.reflect_vector, &intersection->eye_vec);
		if (eye_dot <= 0)
			light_vars.specular = return_tuple(0, 0, 0, COLOR);
		else
		{
			light_vars.specular_fac = pow(eye_dot, light_vars.material->shine);
			light_vars.specular = return_scalar(&light->intensity, light_vars.material->specular * light_vars.specular_fac);
		}
	}
	return (return_colorf(light_vars.diffuse.x + light_vars.specular.x + light_vars.ambient.x, light_vars.diffuse.y + light_vars.specular.y + light_vars.ambient.y, light_vars.diffuse.z + light_vars.specular.z + light_vars.ambient.z));
}

t_light	create_light(t_tuple intensity, t_tuple position)
{
	t_light	light;

	light.intensity = intensity;
	light.position = position;
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
