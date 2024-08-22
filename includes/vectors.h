/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:27:59 by pipolint          #+#    #+#             */
/*   Updated: 2024/08/21 16:12:52 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

typedef struct	s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

t_vector	subtract_vectors(t_vector *vec1, t_vector *vec2);
void		set_vector_points(t_vector *v, double x, double y, double z);
double		dot_product(t_vector *vec1, t_vector *vec2);
void 		normalize(t_vector *vector);
t_vector	add_vectors(t_vector *vec1, t_vector *vec2);
void		scalar(t_vector *vec, double scalar);
t_vector	return_scalar(t_vector *vec, double scalar);
void		negate(t_vector *to_negate);

#endif