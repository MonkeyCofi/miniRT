/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/08/20 19:40:44 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	draw_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*p;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		 p = mlx->img.img_addr + (y * mlx->img.line_length) + (x * (mlx->img.bpp / 8));
		 *(unsigned int *)p = color;
	}
	return ;
}

void	set_min_max(t_vector *color)
{
	if (color->x < 0)
		color->x = 0;
	if (color->x > 1)
		color->x = 1;
	if (color->y < 0)
		color->y = 0;
	if (color->y > 1)
		color->y = 1;
	if (color->z < 0)
		color->z = 0;
	if (color->z > 1)
		color->z = 1;
}

int	get_ray_color(t_color	*color)
{
	int8_t	r;
	int8_t	g;
	int8_t	b;
	int8_t	a;
	int	res;

	//set_min_max(&color->color);
	r = color->color.x * 255;
	g = color->color.y * 255;
	b = color->color.z * 255;
	a = color->alpha;
	res = a << 24 | r << 16 | g << 8 | b;
	return (res);
}

double	magnitude(t_vector *vec)
{
	return (sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z));
}

//int	return_color(t_mlx *mlx, t_camera *cam, t_vector *ray)
int	shoot_ray(t_mlx *mlx, t_camera *cam, int i, int j)
{
	double		a;
	double		b;
	double		c;
	double		disc;
	t_ray		ray;
	t_color		color;

	ft_bzero(&ray, sizeof(t_ray));
	double r = 0.5;
	set_vector_points(&ray.ray, ((double)j / WIDTH * 2 - 1) * cam->asp, (double)i / HEIGHT * 2 - 1, 1);
	a = dot_product(&ray.ray, &ray.ray);
	b = -2.0 * dot_product(&ray.ray, &cam->camera);
	c = dot_product(&cam->camera, &cam->camera) - r * r;
	disc = b * b - (4 * a * c);
	if (disc <= 0)
	{
		color.color.x = 0;
		color.color.y = 50;
		color.color.z = 0;
		color.alpha = 1;
		return (get_ray_color(&color));
	}
	double q0 = (-b - sqrt(disc)) / (2 * a);
	t_vector ray_dir = return_scalar(&ray.ray, q0);
	normalize(&ray_dir);
	t_vector hit = add_vectors(&cam->camera, &ray_dir);
	color.color = hit;
	color.alpha = 1;
	color.color.x = 0.5 * hit.x + 1;
	color.color.y = 0.5 * hit.y + 1;
	color.color.z = 0.5 * hit.z + 1;
	(void)mlx;
	return (get_ray_color(&color));
}

void	render(t_mlx *mlx, t_camera *cam)
{
	int			i;
	int			j;
	t_vector	ray;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			//double hit = shoot_ray(mlx, cam, i, j);
			int	color = shoot_ray(mlx, cam, i, j);
			//printf("%d\n", color);
			draw_pixel(mlx, j, i, color);
			j++;
		}
		i++;
	}
	(void)ray;
}

int	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "miniRT");
	if (!mlx->win)
		return (-1);
		// terminate(mlx);
	mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!(mlx->img.img))
		return (-1);
	mlx->img.img_addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bpp, &mlx->img.line_length, &mlx->img.endian);
	if (!APPLE)
		mlx_hook(mlx->win, 2, 1L << 0, escape, mlx);
	else
		mlx_hook(mlx->win, 2, 0, escape, mlx);
	return (1);
}
// ORIGIN + (DIRECTION * POINT ALONG THE RAY))
int main(void)
{
	t_mlx		mlx;
	t_camera	cam;

	init_mlx(&mlx);
	cam = init_cam();
	render(&mlx, &cam);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
	mlx_loop(mlx.mlx);
}
