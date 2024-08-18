/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/08/18 13:46:21 by pipolint         ###   ########.fr       */
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

void	set_ray_color(t_camera *cam, t_ray *ray, int color)
{
	ray->color = color;
	(void)cam;
}

//int	return_color(t_mlx *mlx, t_camera *cam, t_vector *ray)
double	shoot_ray(t_mlx *mlx, t_camera *cam, int i, int j)
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
	return (-b - sqrt(disc / (2 * a)));
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
			//draw_pixel(mlx, j, i, );
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
	//mlx_hook(mlx->win, 17, 0, destroy, mlx);
	if (!APPLE)
		mlx_hook(mlx->win, 2, 1L << 0, escape, mlx);
	else
		mlx_hook(mlx->win, 2, 0, escape, mlx);
	return (1);
}

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
