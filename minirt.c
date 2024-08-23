/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/08/23 13:06:53 by pipolint         ###   ########.fr       */
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

int	intersect_sphere(t_camera *cam, int i, int j)
{
	t_sphere	sphere;
	t_hit		hit;
	double		a;
	double		b;
	double		c;
	double		disc;

	sphere.color = malloc(sizeof(t_color));
	sphere.color->color.x = 0.94;
	sphere.color->color.y = 0.39;
	sphere.color->color.z = 0;
	sphere.radius = 0.5;
	set_vector_points(&hit.hit.origin, cam->camera.x, cam->camera.y, cam->camera.z);
	set_vector_points(&hit.hit.direction, ((double)j / WIDTH * 2 - 1) * cam->asp, ((double)i / HEIGHT * 2 - 1), cam->camera.z);
	a = dot_product(&hit.hit.direction, &hit.hit.direction);
	b = -2.0 * dot_product(&hit.hit.direction, &hit.hit.origin);
	c = dot_product(&hit.hit.origin, &hit.hit.origin) - sphere.radius * sphere.radius;
	disc = b * b - (4 * a * c);
	if (disc < 0)
	{
		sphere.color->color.x = 0.1;
		sphere.color->color.y = 0.5;
		sphere.color->color.z = 0.5;
		sphere.color->alpha = 0.2;
		return (get_ray_color(sphere.color));
	}
	double q0 = (-b + sqrt(disc)) / (2 * a);
	t_vector ray_dir = return_scalar(&hit.hit.direction, q0);
	t_vector light;
	set_vector_points(&light, -1, -1, 1);
	negate(&light);
	hit.hit.direction = add_vectors(&hit.hit.origin, &ray_dir);
	double t = dot_product(&hit.hit.direction, &light);
	scalar(&sphere.color->color, t);
	sphere.color->alpha = 1;
	return (get_ray_color(sphere.color));
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
			int	color = intersect_sphere(cam, i, j);
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

