/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:38:00 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/23 14:55:33 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bool	is_point(t_tuple *vec)
{
	if (vec->w == 1)
		return (true);
	return (false);
}

t_bool	is_vector(t_tuple *vec)
{
	if (vec->w == 0)
		return (true);
	return (false);
}

t_bool	is_equal(double n1, double n2)
{
	if (fabs(n1 - n2) < EPSILON)
		return (true);
	return (false);
}

void	print_tuple_points(t_tuple *vec)
{
	printf("x: %.5f, ", vec->x);
	printf("y: %.5f, ", vec->y);
	printf("z: %.5f, ", vec->z);
	printf("w: %f\n", vec->w);
}
