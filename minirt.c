/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/08/19 19:30:02 by pipolint         ###   ########.fr       */
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

int	get_ray_color(t_color	*color)
{
	int	r;
	int	g;
	int	b;
	int	a;

	r = color->color->x * 255;
	g = color->color->y * 255;
	b = color->color->z * 255;
	a = color->alpha * 255;
	return (a << 24 | r << 16 | g << 8 | b);
}

//int	return_color(t_mlx *mlx, t_camera *cam, t_vector *ray)
int	shoot_ray(t_mlx *mlx, t_camera *cam, int i, int j)
{
	double		a;
	double		b;
	double		c;
	double		disc;
	t_ray		ray;

	ft_bzero(&ray, sizeof(t_ray));
	double r = 0.5;
	set_vector_points(&ray.ray, ((double)j / WIDTH * 2 - 1) * cam->asp, (double)i / HEIGHT * 2 - 1, 1);
	a = dot_product(&ray.ray, &ray.ray);
	b = -2.0 * dot_product(&ray.ray, &cam->camera);
	c = dot_product(&cam->camera, &cam->camera) - r * r;
	disc = b * b - (4 * a * c);
	if (disc <= 0)
		return (-1);
	// for the lower end of the quadratic equation
	{
		double q0 = -b - disc / (2 * a);
		// get the hit normal
		t_vector ray_dir = return_scalar(&ray.ray, cam->focal_length);
		t_vector hit = add_vectors(&cam->camera, &ray_dir);	// origin + direction * current point in the ray
		t_color color;
		color.color = &hit;
		color.alpha = 1;
		draw_pixel(mlx, j, i, get_ray_color(&color));
	}
	{
		double q1 = -b + disc / (2 * a);
		// get the hit normal
		t_vector ray_dir = return_scalar(&ray.ray, cam->focal_length);
		t_vector hit = add_vectors(&cam->camera, &ray_dir);	// origin + direction * current point in the ray
		t_color color;
		color.color = &hit;
		color.alpha = 1;
		draw_pixel(mlx, j, i, get_ray_color(&color));
	}
	return (1);
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
			double hit = shoot_ray(mlx, cam, i, j);
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
