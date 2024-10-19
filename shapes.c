/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 13:17:33 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/19 18:59:57 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	*create_shape(t_shape_type type, void *shape_ptr)
{
	t_shape	*shape;
	
	shape = ft_calloc(1, sizeof(t_shape));
	if (shape == NULL)
		return (NULL);
	shape->inverse_mat = NULL;
	shape->material = create_default_material();
	shape->transform = identity();
	shape->type = type;
	shape->shape = shape_ptr;
	return (shape);
}
