/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:27:59 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/01 20:49:13 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# include "structs.h"

/* Tuple utils */
void		set_vector_points(t_tuple *v, float x, float y, float z);
void		set_point_points(t_tuple *v, float x, float y, float z);
t_tuple		return_tuple(float x, float y, float z, float w);

/* Vector Operations and Arithmetic*/
void 		normalize(t_tuple *vector);
float		magnitude(t_tuple *vector);
void		scalar(t_tuple *vec, double scalar);
void		negate(t_tuple *to_negate);
double		dot_product(t_tuple *vec1, t_tuple *vec2);
t_tuple		subtract_tuples(t_tuple *vec1, t_tuple *vec2);
t_tuple		add_vectors(t_tuple *vec1, t_tuple *vec2);
t_tuple		return_scalar(t_tuple *vec, double scalar);
t_tuple		return_at(t_ray *ray, double t);

/* Vector Utils */
t_bool	is_point(t_tuple *vec);
t_bool	is_vector(t_tuple *vec);
t_bool	is_equal(float n1, float n2);
void	print_tuple_points(t_tuple *vec);

#endif