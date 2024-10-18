/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:27:35 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/19 02:32:11 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mater	*create_default_material()
{
	t_mater	*return_material;

	return_material = ft_calloc(1, sizeof(t_mater));
	if (!return_material)
		return (NULL);
	return_material->ambient = 0.1;
	return_material->diffuse = 0.9;
	return_material->specular = 0.9;
	return_material->shine = 200;
	return_material->color = return_tuplepoint(1, 1, 1, 1);
	return (return_material);
}

t_mater	*create_material(t_tuple color, float diffuse, float ambient, float specular, float shine)
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
	return (ret_mat);
}
