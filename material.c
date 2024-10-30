/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:27:35 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/29 18:14:38 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mater	*create_default_material()
{
	t_mater	*return_material;

	return_material = ft_calloc(1, sizeof(t_mater));
	if (!return_material)
		return (NULL);
	return_material->color = ft_calloc(1, sizeof(t_tuple));
	if (!return_material->color)
		return (NULL);
	return_material->pattern.color_one = ft_calloc(1, sizeof(t_tuple));
	if(!return_material->pattern.color_one)
		return (NULL);
	return_material->pattern.color_two = ft_calloc(1, sizeof(t_tuple));
	if(!return_material->pattern.color_two)
		return (NULL);
	return_material->ambient = 0.01;
	return_material->diffuse = 0.9;
	return_material->specular = 0.9;
	return_material->shine = 200;
	return_color(1, 1, 1, return_material->color);
	return_material->is_patterned = false;
	return_color(0, 0, 0, return_material->pattern.color_one);
	return_color(1, 1, 1, return_material->pattern.color_two);
	return_material->pattern.pattern_scale = 3;
	return (return_material);
}

t_mater	*create_material(t_tuple color, double diffuse, double ambient, double specular, double shine)
{
	t_mater	*ret_mat;

	ret_mat = ft_calloc(1, sizeof(t_mater));
	if (!ret_mat)
		return (NULL);
	ret_mat->color = &color;
	ret_mat->diffuse = diffuse;
	ret_mat->ambient = ambient;
	ret_mat->specular = specular;
	ret_mat->shine = shine;
	ret_mat->is_patterned = false;
	return (ret_mat);
}
