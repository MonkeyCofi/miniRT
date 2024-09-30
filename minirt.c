/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/09/30 19:58:42 by pipolint         ###   ########.fr       */
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

t_tuple	position(t_ray *ray, float t)
{
	t_tuple	ret;

	set_point_points(&ret, \
		(ray->direction.x * t) + ray->origin.x, \
		(ray->direction.y * t) + ray->origin.y, \
		(ray->direction.z * t) + ray->origin.z);
	return (ret);
}
t_bool	sphere_hit(t_minirt *minirt, t_camera *cam, int i, int j)
{
	float	vars[4];
	t_tuple	point;
	t_ray	ray;
	float	intersects[2];

	set_point_points(&point, 0, 0, 0);
	set_point_points(&ray.origin, 0, 0, 0);
	set_vector_points(&ray.direction, 0, 0, 1);
	point = subtract_tuples(&point, &ray.origin);
	vars[0] = dot_product(&ray.direction, &ray.direction);
	vars[1] = 2 * dot_product(&ray.direction, &point);
	vars[2] = dot_product(&point, &point) - 1;
	vars[3] = vars[1] * vars[1] - 4 * vars[0] * vars[2];
	if (vars[3] < 0)
		return (false);
	intersects[0] = (-vars[1] - sqrt(vars[3])) / (2 * vars[0]);
	intersects[1] = (-vars[1] + sqrt(vars[3])) / (2 * vars[0]);
	
	//printf("%.5f\n", intersects[0]);
	//printf("%.5f\n", intersects[1]);
	
	(void)cam;
	(void)minirt;
	(void)i;
	(void)j;
	return (true);
}

//t_bool	sphere_hit(t_minirt *minirt, t_camera *cam, int i, int j)
//{
//	t_tuple		light;
//	t_hit		hit;
//	double		variables[4];
//	double		disc;
//	double		quad;

//	minirt->spheres->inward_normal = false;
//	set_vector_points(&hit.hit.origin, cam->camera.x, cam->camera.y, cam->camera.z);
//	set_vector_points(&hit.hit.direction, ((double)j / WIDTH * 2 - 1) * cam->asp, ((double)i / HEIGHT * 2 - 1), cam->camera.z);
//	set_vector_points(&light, 20, -1, -20);
//	normalize(&light);
//	normalize(&hit.hit.direction);
//	variables[0] = dot_product(&hit.hit.direction, &hit.hit.direction);
//	variables[1] = dot_product(&hit.hit.direction, &hit.hit.origin);
//	variables[2] = dot_product(&hit.hit.origin, &hit.hit.origin) - minirt->spheres->radius * minirt->spheres->radius;
//	disc = variables[1] * variables[1] - (variables[0] * variables[2]);
//	if (disc < 0)
//		return (false);
//	variables[3] = sqrt(disc);
//	quad = (variables[1] - variables[3]) / (variables[0]);
//	if (quad <= T_MIN || T_MAX <= quad)
//	{
//		quad = ((variables[1] + variables[3]) / variables[0]);
//		if (quad <= T_MIN || T_MAX <= quad)
//			return (false);
//	}
//	minirt->spheres->hit.t = quad;
//	minirt->spheres->hit.p = return_at(&hit.hit, minirt->spheres->hit.t);	// the point of intersection of the ray against the sphere
//	minirt->spheres->hit.normal = subtract_tuples(&minirt->spheres->center, &minirt->spheres->hit.p);	// the normal at the point of intersection
//	normalize(&minirt->spheres->hit.normal);
//	if (dot_product(&minirt->spheres->hit.normal, &hit.hit.direction) < 0)
//		minirt->spheres->inward_normal = true;
//	t_tuple color;
//	double	t;
//	t = dot_product(&minirt->spheres->hit.normal, &light);
//	color = return_scalar(&minirt->spheres->color, t);
//	draw_pixel(minirt->mlx, j, i, get_ray_coloraarij(&color));
//	return (true);
//}

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
			sphere_hit(minirt, minirt->cam, i, j);
			j++;
		}
		i++;
	}
	(void)mlx;
	(void)ray;
}

//int main(int argc, char **argv)
//{
//	t_mlx		mlx;
//	t_minirt	*minirt;
	
//	if(argc == 2)
//	{
//		minirt = init_minirt(&mlx);
//		if (!minirt)
//			return (1);
//		if(!fileopen(argv[1], minirt))
//		{
//			init_mlx(&mlx);
//			render(&mlx, minirt);
//			mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
//			mlx_loop(mlx.mlx);
//		}
//		free(minirt->cam);
//		free(minirt);
//	}
//	else
//		printf("Insufficient amount of arguments!\n");
//}

void	draw_pixel_float(t_mlx *mlx, float x, float y, int color)
{
	char	*p;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		p = mlx->img.img_addr + ((int)y * mlx->img.line_length) + \
			((int)x * (mlx->img.bpp / 8));
		*(unsigned int *)p = color;
	}
	return ;
}

void	draw_horizontal_line(t_mlx *mlx, int startx, int starty, int len)
{
	for (int i = 0; i < len; i++)
	{
		draw_pixel(mlx, startx + i, starty, 0xFF0000);
	}
}

void	draw_circle(t_mlx *mlx, int radius, int originx, int originy)
{
	//float a = 0;
	//float b = 0;
	//for (int i = 0; i < 100; i++)
	//{
	//	for (int j = 0; j < 100; j++)
	//	{
	//		//a = i * i;
	//		//b = j * j;
	//			//continue ;
	//		draw_pixel(mlx, i + origin, j + origin, 0xff0000);
	//	}
	//}
	for (int j = originy - (radius * 2); j < originy; j++) {
		for (int i = 0; i < radius * 2; i++)
			draw_horizontal_line(mlx, originx - i, j, (radius * 2) - i );
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	(void)radius;
}

int main(void)
{
	t_mlx	mlx;
	
	init_mlx(&mlx);
	draw_circle(&mlx, 50, 200, 200);
	mlx_loop(mlx.mlx);
	//draw_pixel()
}