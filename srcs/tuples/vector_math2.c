/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:14:20 by ahaarij           #+#    #+#             */
/*   Updated: 2024/11/25 19:14:33 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	return_at(t_ray *ray, double t)
{
	t_tuple	new;

	new = return_scalar(&ray->direction, t);
	return (add_vectors(&ray->origin, &new));
}

void	matrix_cross(t_tuple *a, t_tuple *b, t_4dmat res)
{
	a->x = b->x * res.matrix[0][0] + b->y * res.matrix[1][0] + b->z * \
	res.matrix[2][0] + b->w * res.matrix[3][0];
	a->y = b->x * res.matrix[0][1] + b->y * res.matrix[1][1] + b->z * \
	res.matrix[2][1] + b->w * res.matrix[3][1];
	a->z = b->x * res.matrix[0][2] + b->y * res.matrix[1][2] + b->z * \
	res.matrix[2][2] + b->w * res.matrix[3][2];
	a->w = b->x * res.matrix[0][3] + b->y * res.matrix[1][3] + b->z * \
	res.matrix[2][3] + b->w * res.matrix[3][3];
}
