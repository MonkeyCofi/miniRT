/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:18:08 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/10 21:08:10 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	t_bool shadow)
{
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
	}
	return (return_colorf(vars->diffuse.x + \
	vars->ambient.x, vars->diffuse.y + vars->ambient.y, vars->diffuse.z \
	+ vars->ambient.z));
}

t_tuple	lighting(t_inter_comp *intersection, t_light *light, \
	t_bool in_shadow, t_minirt *m)
{
	t_lighting	vars;

	vars.material = intersection->material;
	vars.color = vars.material->color;
	vars.final_color = multiply_tuples(&light->intensity, &vars.color, COLOR);
	vars.final_color = return_scalar(&vars.final_color, light->brightness);
	vars.light_vector = subtract_tuples(&intersection->point, &light->position);
	normalize(&vars.light_vector);
	vars.ambient = return_scalar(&vars.final_color, vars.material->ambient);
	vars.light_dot = dot_product(&intersection->normal_vec, &vars.light_vector);
	(void)m;
	return (get_diffuse_specular(intersection, &vars, in_shadow));
}
