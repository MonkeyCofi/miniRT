/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 21:06:39 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/24 20:21:03 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "structs.h"

//void	draw_pixel(t_mlx *mlx, int x, int y, int color);
//t_ray	*ray_per_pixel(t_camera *camera, int px, int py);
//static inline t_ray	*ray_per_pixel(t_camera *camera, int px, int py);
int		render(t_mlx *mlx, t_camera *camera, t_minirt *minirt);
t_ray	ray_per_pixel(t_camera *camera, int px, int py);
void	draw_pixel(t_mlx *mlx, int x, int y, int color);

#endif