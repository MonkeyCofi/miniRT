/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:18:08 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/28 21:41:17 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	cylinder_cone_pattern(t_inter_comp *inter, t_lighting *light)
{
	t_tuple	obj_point;
	double	y_value;
	double	min_y;
	double	max_y;

	min_y = ((t_cylinder *)(inter->obj->shape))->minimum;
	max_y = ((t_cylinder *)(inter->obj->shape))->maximum;
	obj_point = tuple_mult_fast(&inter->obj->inverse_mat, \
		&inter->point_adjusted);
	y_value = obj_point.y;
	if (fabs(y_value - min_y) < EPSILON || fabs(y_value - max_y) < EPSILON)
		light->color = checkerboard_cap(light->material->pattern, obj_point);
	else
		light->color = checkerboard_cylinder(light->material->pattern, inter);
}

static void	check_shape_pattern(t_inter_comp *inter, t_lighting *vars)
{
	t_tuple	object_point;
	t_tuple	normal;

	if (inter->type == CYLINDER || inter->type == CONE)
		cylinder_cone_pattern(inter, vars);
	else if (inter->type == SPHERE)
	{
		if (vars->material->is_patterned)
			vars->color = checkerboard_sphere(vars->material->pattern, \
				inter);
		else
			vars->color = vars->material->color;
		if (vars->material->texture)
			inter->normal_vec = normal_from_sample(inter);
	}
	else
	{
		object_point = tuple_mult_fast(&inter->obj->inverse_mat, &inter->point);
		normal = inter->obj->normal(inter->obj->shape, object_point);
		normalize(&normal);
		vars->color = checkerboard(vars->material->pattern, \
			object_point, normal);
	}
}

static t_tuple	get_reflected_ray(t_tuple *from, t_tuple *normal)
{
	double	dot;
	double	prod;
	t_tuple	_scalar;

	dot = dot_product(from, normal);
	prod = 2 * dot;
	_scalar = return_scalar(normal, prod);
	return (subtract_tuples(&_scalar, from));
}

static t_tuple	get_diffuse_specular(t_inter_comp *inter, t_lighting *vars, \
	t_bool shadow, t_light *light)
{
	double	eye_dot;

	if (shadow || vars->light_dot < 0)
		return (vars->ambient);
	else
	{
		vars->diffuse = return_scalar(&vars->final_color, \
			vars->material->diffuse * vars->light_dot);
		vars->vec_to_light = return_tuple(-vars->light_vector.x, \
			-vars->light_vector.y, -vars->light_vector.z, VECTOR);
		vars->reflect_vector = get_reflected_ray(&vars->vec_to_light, \
			&inter->normal_vec);
		eye_dot = dot_product(&vars->reflect_vector, &inter->eye_vec);
		if (eye_dot <= 0)
			vars->specular = return_tuple(0, 0, 0, COLOR);
		else
		{
			vars->specular_fac = pow(eye_dot, vars->material->shine);
			vars->specular = return_scalar(&light->intensity, \
				vars->material->specular * vars->specular_fac);
		}
	}
	return (return_colorf(vars->diffuse.x + vars->specular.x + vars->ambient.x, \
		vars->diffuse.y + vars->specular.y + vars->ambient.y, vars->diffuse.z + \
			vars->specular.z + vars->ambient.z));
}

t_tuple	lighting(t_inter_comp *intersection, t_light *light, \
	t_bool in_shadow, t_minirt *m)
{
	t_lighting	vars;

	vars.material = intersection->material;
	if (vars.material->is_patterned == true)
		check_shape_pattern(intersection, &vars);
	else
		vars.color = vars.material->color;
	vars.final_color = multiply_tuples(&light->intensity, &vars.color, COLOR);
	vars.final_color = return_scalar(&vars.final_color, \
		light->brightness);
	vars.light_vector = subtract_tuples(&intersection->point_adjusted, \
		&light->position);
	normalize(&vars.light_vector);
	vars.ambient = return_scalar(&vars.final_color, vars.material->ambient);
	vars.light_dot = dot_product(&intersection->normal_vec, &vars.light_vector);
	(void)m;
	return (get_diffuse_specular(intersection, &vars, in_shadow, light));
}
