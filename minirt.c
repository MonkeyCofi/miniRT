/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/17 16:13:26 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_shapes(t_minirt *minirt);

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

void	print_4d_points(float points[4][4])
{
	int	i;
	int	j;
	
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			printf("%.3f ", points[i][j]);
		printf("\n");
	}
}

t_ray	*ray_per_pixel(t_camera *camera, int px, int py)
{
	float	x_offset;
	float	y_offset;
	float	world_x;
	float	world_y;
	t_4dmat	*camera_inverse;
	t_tuple	*pixel;
	t_tuple	*origin;
	t_tuple	direction;
	t_tuple	temp;
	
	x_offset = (px + 0.5) * camera->pixel_size;
	y_offset = (py + 0.5) * camera->pixel_size;
	world_x = camera->half_width - x_offset;
	world_y = camera->half_height - y_offset;
	if (inverse_mat(camera->view_matrix, &camera_inverse) == false)
		return (NULL);
	temp = return_tuple(world_x, world_y, -1, POINT);
	pixel = tuple_mult(camera_inverse, &temp);
	temp = return_tuple(0, 0, 0, POINT);
	origin = tuple_mult(camera_inverse, &temp);
	direction = subtract_tuples(origin, pixel);
	normalize(&direction);
	return (create_ray(*origin, direction));
}

int	get_key_pressed(int keycode, t_mlx *mlx, t_sphere *sphere)
{
	if (keycode == PLUS)
		transform_sphere(sphere, scale, return_tuple(1, 2, 1, POINT));
	else if (keycode == ESC)
		exit(1);
	(void)mlx;
	return (0);
}

void	render(t_mlx *mlx, t_camera *camera, t_minirt *minirt)
{
	int		i;
	int		j;
	t_ray	*ray;
	t_color c;
	t_tuple color;

	i = -1;
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

int main(void)
{
	t_mlx		mlx;
	t_minirt 	*m;
	t_camera	camera;
	t_tuple		from;
	t_tuple		to;
	t_tuple		up;

	init_mlx(&mlx);
	m = init_default(&mlx);
	camera = return_camera(WIDTH, HEIGHT, 90, NULL);
	from = return_tuple(0, 0.2, -1, POINT);
	to = return_tuple(0, 0, 0, POINT);
	up = return_tuple(0, 1, 0, VECTOR);
	camera.view_matrix = view_transform(&to, &from, &up);
	render(&mlx, &camera, m);
	mlx_loop(&mlx.mlx);
}
