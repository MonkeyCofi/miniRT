/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:05:33 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/08 21:08:48 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "structs.h"

t_sphere	*create_sphere(float originx, float originy, float originz, t_mater *material);
t_bool		sphere_hit(t_minirt *minirt, t_camera *cam, t_intersects *inter, t_ray *ray, t_sphere *sphere, int with_transform);
void		render_sphere(t_mlx *mlx, t_minirt *m);

#endif