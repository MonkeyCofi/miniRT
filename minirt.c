/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/08/09 16:31:14 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	destroy(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
}

int	escape(int keycode, void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (keycode == ESC)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	return (1);
}

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

// double dot_product(double v[3], double u[3])
// {
// 	double	result;
// 	int		i;

// 	while (i < 3)
// 		result += v[i] * u[i];
//     // double result = 0.0;
//     // for (int i = 0; i < 3; i++)
//     //     result += v[i] * u[i];
//     return result;
// }

double dot_product(t_vector *vec1, t_vector *vec2)
{
	double	result;
	int		i;

	result = 0;
	result += vec1->x * vec2->x;
	result += vec1->y * vec2->y;
	result += vec1->z * vec2->z;
    return (result);
}

void normalize(t_vector *vector)
{
	double	magnitude;

	magnitude = sqrt(dot_product(vector, vector));
	vector->x /= magnitude;
	vector->y /= magnitude;
	vector->z /= magnitude;
}

// void render(t_mlx *mlx, double camera[3])
// {
// 	double ball[3] = {0};
	
// 	for (int i = 0; i < WIDTH; i++)
// 	{
// 		for (int j = 0; j < HEIGHT; j++)
// 		{
// 			double dir[3];
// 			dir[0] = (double)i / WIDTH * 2 - 1;
// 			dir[1] = (double)j / HEIGHT * 2 - 1;
// 			dir[2] = 1;
// 			double res[3];
// 			normalize(dir, res, res + 1, res + 2);
// 			double a = dot_product(res, res);
// 			res[0] *= -2;
// 			res[1] *= -2;
// 			res[2] *= -2;
// 			double b = dot_product(res, camera);
// 			double c = dot_product(camera, camera) - 1;
// 			if (b * b - 4 * a * c <= 0)
// 				draw_pixel(mlx, i, j, 0);
// 			else
// 			{
// 				res[0] /= -2;
// 				res[1] /= -2;
// 				res[2] /= -2;
// 				double pos[3];
// 				double dist = (-b - sqrt(b*b - 4 * a * c)) / (2 * a);
// 				//pos = camera + dist * dir;
// 				pos[0] = camera[0] + dist * dir[0];
// 				pos[1] = camera[1] + dist * dir[1];
// 				pos[2] = camera[2] + dist * dir[2];
// 				double normed[3];
// 				// normalize(pos, normed, normed + 1, normed + 2);
// 				double intensity = dot_product(pos, (double[]){-0.408248, 0.408248, -0.816497});
// 				double color = intensity * 0x0000ff;
// 				draw_pixel(mlx, i, j, color);		
// 			}
// 		}
// 	}
// }

void	render(t_mlx *mlx, t_camera *cam)
{
	float		a;
	float		b;
	float		c;
	float		discriminant;
	int			i;
	int			j;
	t_vector	ray;
	t_vector	circle;

	i = 0;
	j = 0;
	// a = ray_origin; the camera position
	// b = ray_direction; the direction in which the ray is going
	// c = radius; the radius of the sphere/circle
	// discriminant = b * b - 4 * a * c;

	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			ray.y = i * HEIGHT / 2 - 1;
			ray.x = j * WIDTH / 2 - 1;
			ray.z = 1;
			normalize(&ray);
			a = dot_product(&ray, &ray);
			b = 2 * dot_product(&ray, &cam->camera);
			c = dot_product(&cam->camera, &cam->camera) - 0.5 * 0.5;
			double equ = (b * b) - (4 * a * c);
			if (equ >= 0)
				draw_pixel(mlx, j, i, 0xffff00ff);
			else
				draw_pixel(mlx, j, i, 0x000000);
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
		// terminate(mlx);
	mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!(mlx->img.img))
		return (-1);
	mlx->img.img_addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bpp, &mlx->img.line_length, &mlx->img.endian);
	mlx_hook(mlx->win, 17, 0, destroy, mlx);
	if (!APPLE)
		mlx_hook(mlx->win, 2, 1L << 0, escape, mlx);
	else
		mlx_hook(mlx->win, 2, 0, escape, mlx);
}

int main(void)
{
	t_mlx		mlx;
	t_camera	cam;

	init_mlx(&mlx);
	// render(&mlx, (double[]){0, -10, 0});
	cam = init_cam(&mlx);
	render(&mlx, &cam);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
	mlx_loop(mlx.mlx);
}
