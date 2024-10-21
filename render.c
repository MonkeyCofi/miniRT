/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 21:06:15 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/21 21:06:23 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	draw_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*p;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		p = mlx->img.img_addr + (y * mlx->img.line_length) + \
			(x * (mlx->img.bpp / 8));
		*(unsigned int *)p = color;
	}
	return ;
}

t_ray	*ray_per_pixel(t_camera *camera, int px, int py)
{
	float	x_offset;
	float	y_offset;
	float	world_x;
	float	world_y;
	t_tuple	*pixel;
	t_tuple	*origin;
	t_tuple	direction;
	t_tuple	temp;
	
	x_offset = (px + 0.5) * camera->pixel_size;
	y_offset = (py + 0.5) * camera->pixel_size;
	world_x = camera->half_width - x_offset;
	world_y = camera->half_height - y_offset;
	temp = return_tuple(world_x, world_y, -1, POINT);
	pixel = tuple_mult(camera->inverse, &temp);
	temp = return_tuple(0, 0, 0, POINT);
	origin = tuple_mult(camera->inverse, &temp);
	direction = subtract_tuples(origin, pixel);
	normalize(&direction);
	return (create_ray(*origin, direction));
}

void	render(t_mlx *mlx, t_camera *camera, t_minirt *minirt)
{
	int		i;
	int		j;
	t_ray	*ray;
	t_color c;
	t_tuple color;

	i = -1;
	if (inverse_mat(camera->view_matrix, &camera->inverse) == false)
		return ;
	while (++i < camera->horizontal_canv_size)
	{
		j = -1;
		while (++j < camera->vertical_canv_size)
		{
			ray = ray_per_pixel(camera, j, i);
			color = color_at(minirt, ray);
			c.colors = return_tuple(color.x, color.y, color.z, COLOR);
			draw_pixel(mlx, j, i, get_ray_color(&c));
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
}
