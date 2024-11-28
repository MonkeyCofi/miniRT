/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 13:17:33 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/26 09:37:24 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	*create_shape(t_shape_type type, void *shape_ptr)
{
	t_shape	*shape;

	shape = ft_calloc(1, sizeof(t_shape));
	if (shape == NULL)
		return (NULL);
	shape->transform = identity();
	inverse_mat_test(&shape->transform, &shape->inverse_mat);
	shape->inverse_transpose = transpose(&shape->inverse_mat);
	shape->type = type;
	shape->shape = shape_ptr;
	shape->translation_mat = identity();
	shape->rotation_mat = identity();
	shape->scaling_mat = identity();
	assign_normal_intersect_func(shape, type);
	return (shape);
}

void	assign_normal_intersect_func(t_shape *shape, t_shape_type type)
{
	if (type == SPHERE)
	{
		shape->normal = normal_sphere;
		shape->intersect = sphere_hit;
	}
	else if (type == PLANE)
	{
		shape->normal = normal_pos_plane;
		shape->intersect = intersect_plane;
	}
	else if (type == CYLINDER)
	{
		shape->normal = normal_pos_cylinder;
		shape->intersect = intersect_cylinder;
	}
	else if (type == CONE)
	{
		shape->normal = normal_pos_cone;
		shape->intersect = intersect_cone;
	}
}
