/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:27:35 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/09 14:18:03 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mater	*create_default_material(t_minirt *m)
{
	t_mater	*return_material;

	return_material = calloc_and_check(sizeof(t_mater), 1, m, "Error: Material: \
		Cannot allocate memory for material");
	return_material->ambient = 0.01;
	return_material->diffuse = 0.9;
	return_material->specular = 0;
	return_material->shine = 200;
	return_color(1, 1, 1, &return_material->color);
	return_material->is_patterned = false;
	return_color(0, 0, 0, &return_material->pattern.color_one);
	return_color(1, 1, 1, &return_material->pattern.color_two);
	return_material->pattern.pattern_scale = 3;
	return (return_material);
}
