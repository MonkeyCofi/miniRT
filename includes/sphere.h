/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:05:33 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/27 09:37:01 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "structs.h"

t_sphere	*create_sphere(t_minirt *m, double radius);

t_bool		sphere_hit(t_minirt *minirt, t_intersects *inter, \
										t_ray *ray, int shape_index);

t_tuple		*normal_sphere_test(t_shape *shape, t_tuple pos);

t_tuple		normal_sphere(t_shape *shape, t_tuple pos);

#endif