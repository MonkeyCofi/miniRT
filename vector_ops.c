/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:28:06 by pipolint          #+#    #+#             */
/*   Updated: 2024/09/26 22:18:12 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

/*
	** if a vector and a vector are added, the resultant tuple is still a vector
	** if a vector and a point are added, the resultant tuple is a point; the new point from point along the vector
	** adding two points doesn't make sense
	** similarly, if a vector was subtracted from a vector, the resultant tuple is still a vector
	** subtracting a vector(w = 0) from a point(w = 1) gives you a new point; the point from original point moved backwards by the vector
	** subtracting two points, p1 and p2, gives you the vector pointing from p2 to p1
	** subtracting a point(w=1) from a vector(w=0) doesn't make sense
*/

void	set_vector_points(t_vector *v, float x, float y, float z)
{
	v->x = x;
	v->y = y;
	v->z = z;
	v->w = 0;
}

void	set_point_points(t_vector *v, float x, float y, float z)
{
	v->x = x;
	v->y = y;
	v->z = z;
	v->w = 1;
}

double dot_product(t_vector *vec1, t_vector *vec2)
{
	return ((vec1->x * vec2->x) + (vec1->y * vec2->y) + (vec1->z * vec2->z));
}

t_vector	cross_product(t_vector *vec1, t_vector *vec2)
{
	t_vector	cross;

	ft_bzero(&cross, sizeof(t_vector));
	(void)vec1;
	(void)vec2;
	return (cross);
}

void normalize(t_vector *vector)
{
	double	magnitude;

	magnitude = sqrt(dot_product(vector, vector));
	vector->x /= magnitude;
	vector->y /= magnitude;
	vector->z /= magnitude;
}

void	negate(t_vector *to_negate)
{
	to_negate->x = -(to_negate->x);
	to_negate->y = -(to_negate->y);
	to_negate->z = -(to_negate->z);
	to_negate->w = -(to_negate->w);
}