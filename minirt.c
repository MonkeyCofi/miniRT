/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/08/23 12:09:18 by ahaarij          ###   ########.fr       */
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

int	shoot_ray( t_camera *cam, int i, int j)
{
	double		a;
	double		b;
	double		c;
	double		disc;
	t_ray		ray;
	t_color		color;

	ft_bzero(&ray, sizeof(t_ray));
	double r = 0.5;
	set_vector_points(&ray.origin, cam->camera.x, cam->camera.y, cam->camera.z);
	set_vector_points(&ray.direction, ((double)j / WIDTH * 2 - 1) * cam->asp, ((double)i / HEIGHT * 2 - 1), cam->camera.z);
	a = dot_product(&ray.direction, &ray.direction);
	b = -2.0 * dot_product(&ray.direction, &ray.origin);
	c = dot_product(&ray.origin, &ray.origin) - r * r;
	disc = b * b - (4 * a * c);
	if (disc < 0)
	{
		color.color.x = 0.1;
		color.color.y = 0.5;
		color.color.z = 0.5;
		color.alpha = 0.2;
		return (get_ray_color(&color));
	}
	double q0 = (-b + sqrt(disc)) / (2 * a);
	t_vector ray_dir = return_scalar(&ray.direction, q0);
	t_vector light;
	set_vector_points(&light, -1, -1, 1);
	negate(&light);
	t_vector hit = add_vectors(&ray.origin, &ray_dir);
	double t = dot_product(&hit, &light);
	color.color.x = 0.94;
	color.color.y = 0.39;
	color.color.z = 0;
	scalar(&color.color, t);
	color.alpha = 1;
	return (get_ray_color(&color));
}

void	render(t_mlx *mlx, t_camera *cam)
{
	int			i;
	int			j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			int	color = shoot_ray(cam, i, j);
			draw_pixel(mlx, j, i, color);
			j++;
		}
		i++;
	}
}

int	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "miniRT");
	if (!mlx->win)
		return (-1);
	mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!(mlx->img.img))
		return (-1);
	mlx->img.img_addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bpp, &mlx->img.line_length, &mlx->img.endian);
	if (!APPLE)
	{
		mlx_hook(mlx->win, 2, 1L << 0, escape, mlx);
	}
	else
	{
		mlx_hook(mlx->win, 2, 0, escape, mlx);
		mlx_hook(mlx->win, 17, 0, destroy, mlx);
	}
	return (1);
}

int main(int argc, char **argv)
{
	t_mlx		mlx;
	t_camera	cam;
	t_cameraparse camp;
	camp.flag = 0;
	(void)argc;
	if(argc == 2)
	{
		if(!fileopen(argv[1], &camp)){
			init_mlx(&mlx);
			cam = init_cam();
			render(&mlx, &cam);
				mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
			mlx_loop(mlx.mlx);
		}	
	}
	else
		printf("Insufficient amount of arguments!\n");
	// init_mlx(&mlx);
	// cam = init_cam();
	// render(&mlx, &cam);
	// mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
	// mlx_loop(mlx.mlx);
}

