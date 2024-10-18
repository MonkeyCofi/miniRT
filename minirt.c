/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/18 21:44:34 by pipolint         ###   ########.fr       */
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
	t_4dmat		temp;

	init_mlx(&mlx);
	m = init_default(&mlx);
	camera = return_camera(WIDTH, HEIGHT, DEG_RAD(120), NULL);
	from = return_tuple(0, 0, -1, POINT);
	to = return_tuple(0, 0, 0, POINT);
	up = return_tuple(0, 1, 0, VECTOR);
	camera.view_matrix = view_transform(&to, &from, &up);
	temp = y_rotation_mat(DEG_RAD(35));
	camera.view_matrix = mat4d_mult_fast(&temp, camera.view_matrix);
	//temp = translation_mat(0, 0, -1);
	//camera.view_matrix = mat4d_mult_fast(&temp, camera.view_matrix);
	//temp = y_rotation_mat(DEG_RAD(40));
	//camera.view_matrix = mat4d_mult_fast(&temp, camera.view_matrix);
	//temp = translation_mat(0, 0, 1);
	//camera.view_matrix = mat4d_mult_fast(&temp, camera.view_matrix);
	render(&mlx, &camera, m);
	(void)temp;
	mlx_loop(&mlx.mlx);
}

//int main(void)
//{
//	t_tuple	point = return_tuple(0, 3, -2, POINT);
//	t_tuple	direction = return_tuple(0, -1, 2, VECTOR);
//	t_cylinder *cylinder = create_cylinder(return_tuple(0, 0, 0, VECTOR));
//	cylinder->minimum = 1;
//	cylinder->maximum = 2;
//	cylinder->is_closed = true;
//	normalize(&direction);
//	t_intersects *inter = ft_calloc(1, sizeof(t_intersects));
//	t_ray	*ray = create_ray(point, direction);
//	cylinder_hit(NULL, inter, ray, cylinder);
//	print_intersects(inter);
//	//t_tuple *normal = normal_pos_cylinder(cylinder, point);
//	//printf("Normal: ");
//	//print_tuple_points(normal);
//}