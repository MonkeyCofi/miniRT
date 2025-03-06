/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 21:06:39 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/10 18:50:35 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "structs.h"

int		render(t_mlx *mlx, t_camera *camera, t_minirt *minirt);
t_ray	ray_per_pixel(t_camera *camera, int px, int py);
void	draw_pixel(t_mlx *mlx, int x, int y, int color);

#endif