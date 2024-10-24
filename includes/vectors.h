/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:27:59 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/24 17:37:13 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# include "structs.h"

/* Tuple utils */
void		set_vector_points(t_tuple *v, double x, double y, double z);
void		set_point_points(t_tuple *v, double x, double y, double z);
t_tuple		return_tuple(double x, double y, double z, double w);
t_tuple		*return_tuple_pointer(double x, double y, double z, double w);
t_ray		*create_ray(t_tuple origin, t_tuple direction);
t_ray		create_ray_static(t_tuple origin, t_tuple direction);

/* Vector Operations and Arithmetic*/
void 		normalize(t_tuple *vector);
double		magnitude(t_tuple *vector);
void		scalar(t_tuple *vec, double scalar);
void		negate(t_tuple *to_negate);
double		dot_product(t_tuple *vec1, t_tuple *vec2);
t_tuple		cross_product(t_tuple *vec1, t_tuple *vec2);
t_tuple		multiply_tuples(t_tuple *tup1, t_tuple *tup2, int vec_point);
t_tuple		subtract_tuples(t_tuple *vec1, t_tuple *vec2);
t_tuple		add_vectors(t_tuple *vec1, t_tuple *vec2);
t_tuple		return_scalar(t_tuple *vec, double scalar);
t_tuple		return_at(t_ray *ray, double t);

/* Vector Utils */
t_bool	is_point(t_tuple *vec);
t_bool	is_vector(t_tuple *vec);
t_bool	is_equal(double n1, double n2);
void	print_tuple_points(t_tuple *vec);

#endif