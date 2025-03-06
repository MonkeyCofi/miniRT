/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:27:35 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/05 20:22:25 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mater	*create_default_material(t_minirt *m)
{
	t_mater	*return_material;

	return_material = calloc_and_check(sizeof(t_mater), 1, m, "Error\nMaterial: \
		Cannot allocate memory for material");
	return_material->ambient = 0.01;
	return_material->diffuse = 0.9;
	return_material->specular = 0;
	return_material->shine = 200;
	return_color(1, 1, 1, &return_material->color);
	return_material->is_patterned = false;
	return (return_material);
}
