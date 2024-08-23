/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/08/23 18:49:48 by pipolint         ###   ########.fr       */
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

//int	intersect_sphere(t_camera *cam, int i, int j)
t_bool	sphere_hit(t_camera *cam, int i, int j)
{
	t_sphere	sphere;
	t_vector 	light;
	t_hit		hit;
	double		variables[3];
	double		disc;
	double		quad;

	sphere.color = malloc(sizeof(t_color));
	sphere.color->color.x = 0.94;
	sphere.color->color.y = 0.39;
	sphere.color->color.z = 0;
	sphere.radius = 0.5;
	set_vector_points(&hit.hit.origin, cam->camera.x, cam->camera.y, cam->camera.z);
	set_vector_points(&hit.hit.direction, ((double)j / WIDTH * 2 - 1) * cam->asp, ((double)i / HEIGHT * 2 - 1), cam->camera.z);
	variables[0] = dot_product(&hit.hit.direction, &hit.hit.direction);
	variables[1] = dot_product(&hit.hit.direction, &hit.hit.origin);
	variables[2] = dot_product(&hit.hit.origin, &hit.hit.origin) - sphere.radius * sphere.radius;
	disc = variables[1] * variables[1] - (variables[0] * variables[2]);
	if (disc < 0)
		return (false);
	quad = (variables[1] + sqrt(disc)) / (variables[0]);
	printf("%f\n", quad);
	sphere.normal = return_scalar(&hit.hit.direction, quad);
	hit.hit.direction = add_vectors(&hit.hit.origin, &sphere.normal);
	sphere.hit.t = dot_product(&hit.hit.direction, &light); 
	return (false);
}

void	render(t_mlx *mlx, t_minirt *minirt)
{
	int			i;
	int			j;
	t_ray		ray;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			//int	color = intersect_sphere(cam, i, j);
			sphere_hit(cam, i, j);
			//draw_pixel(mlx, j, i, color);
			j++;
		}
		i++;
	}
	(void)mlx;
	(void)ray;
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
	t_minirt	* minirt;

	minirt = malloc(sizeof(minirt));
	minirt->cam = malloc(sizeof(t_camera));
	minirt->cam->flag = false;
	if(argc == 2)
	{
		if(!fileopen(argv[1], minirt)){
			init_mlx(&mlx);
			init_cam(minirt);
			render(&mlx, minirt);
				mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
			mlx_loop(mlx.mlx);
		}
	}
	else
		printf("Insufficient amount of arguments!\n");
}

