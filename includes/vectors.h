/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:27:59 by pipolint          #+#    #+#             */
/*   Updated: 2024/08/23 15:48:25 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# include "structs.h"

void		set_vector_points(t_vector *v, double x, double y, double z);
void 		normalize(t_vector *vector);
void		scalar(t_vector *vec, double scalar);
void		negate(t_vector *to_negate);
double		dot_product(t_vector *vec1, t_vector *vec2);
t_vector	subtract_vectors(t_vector *vec1, t_vector *vec2);
t_vector	add_vectors(t_vector *vec1, t_vector *vec2);
t_vector	return_scalar(t_vector *vec, double scalar);
t_vector	return_at(t_ray *ray, double t);

#endif