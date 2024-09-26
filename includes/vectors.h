/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:27:59 by pipolint          #+#    #+#             */
/*   Updated: 2024/09/26 22:08:51 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# include "structs.h"

void		set_vector_points(t_vector *v, float x, float y, float z);
void		set_point_points(t_vector *v, float x, float y, float z);
void 		normalize(t_vector *vector);
void		scalar(t_vector *vec, double scalar);
void		negate(t_vector *to_negate);
double		dot_product(t_vector *vec1, t_vector *vec2);
t_vector	subtract_vectors(t_vector *vec1, t_vector *vec2);
t_vector	add_vectors(t_vector *vec1, t_vector *vec2);
t_vector	return_scalar(t_vector *vec, double scalar);
t_vector	return_at(t_ray *ray, double t);

/* Vector Utils */
t_bool	is_point(t_vector *vec);
t_bool	is_vector(t_vector *vec);
t_bool	is_equal(float n1, float n2);
void	print_vector_points(t_vector *vec);

#endif