/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/02 20:12:49 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	transform_ray(t_ray *old_ray, t_trans type, t_tuple transform_coords, t_sphere *sphere)
{
	t_ray	new_ray;
	t_4dmat	trans_ray;
	t_4dmat	*res;
	
	new_ray.origin = return_tuple(0, 0, 0, 1);
	new_ray.direction = return_tuple(0, 0, 0, 0);
	if (type == translate)
	{
		new_ray.origin = translate_ray(&old_ray->origin, transform_coords.x, transform_coords.y, transform_coords.z);
		new_ray.direction = translate_ray(&old_ray->direction, transform_coords.x, transform_coords.y, transform_coords.z);
	}
	else if (type == scale)
	{
		trans_ray = scaling_mat(transform_coords.x, transform_coords.y, transform_coords.z);
		res = mat4d_mult(&trans_ray, &sphere->transform);
		copy_mat(&sphere->transform, res);
		new_ray.origin = scale_ray(&old_ray->origin, sphere, transform_coords.x, transform_coords.y, transform_coords.z);
		new_ray.direction = scale_ray(&old_ray->direction, sphere, transform_coords.x, transform_coords.y, transform_coords.z);
	}
	return (new_ray);
}

void	sort_intersects(t_intersects *intersects)
{
	int				i;
	int				j;
	int				count;
	t_intersection	temp;

	i = 0;
	if (intersects->intersection_count < MAX_INTERSECTS)
		count = intersects->intersection_count;
	else
		count = MAX_INTERSECTS;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if (intersects->intersections[i].t > intersects->intersections[j].t)
			{
				temp = intersects->intersections[i];
				intersects->intersections[i] = intersects->intersections[j];
				intersects->intersections[j] = temp;
			}
			j++;
		}
		i++;
	}
}

float	best_hit(t_intersects *intersects)
{
	int		i;
	int		count;
	float	res;

	i = -1;
	res = -1;
	if (intersects->intersection_count < MAX_INTERSECTS)
		count = intersects->intersection_count;
	else
		count = MAX_INTERSECTS;
	//sort_intersects(intersects);
	while (++i < count)
	{
		if (intersects->intersections[i].t < 0)
			continue ;
		res = intersects->intersections[i].t;
		intersects->last_intersection = i;
		break ;
	}
	if (i == count && res == 0)
		return (-1);
	return (res);
}

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

t_sphere	*create_sphere(float originx, float originy, float originz)
{
	t_sphere	*ret;

	ret = ft_calloc(1, sizeof(t_sphere));
	if (!ret)
		return (NULL);
	ret->center = return_tuple(originx, originy, originz, 1);
	ret->color = return_tuple(0.8, 0.5, 0.3, 0);
	ret->radius = 1;
	ret->transform = identity();
	return (ret);
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

t_bool	sphere_hit(t_minirt *minirt, t_camera *cam, t_intersects *inter, t_ray *ray, t_sphere *sphere)
{
	float	vars[4];
	t_tuple	sphere_dist;

	sphere_dist = subtract_tuples(&sphere->center, &ray->origin);
	//sphere_dist = subtract_tuples(&ray->origin, &sphere->center);
	vars[0] = dot_product(&ray->direction, &ray->direction);
	vars[1] = 2 * dot_product(&sphere_dist, &ray->direction);
	vars[2] = dot_product(&sphere_dist, &sphere_dist) - (sphere->radius * sphere->radius);
	vars[3] = (vars[1] * vars[1]) - (4 * vars[0] * vars[2]);
	if (vars[3] < 0)
		return (false);
	inter->intersections[inter->intersection_count].t = (-vars[1] - sqrt(vars[3])) / (2 * vars[0]);
	if (inter->intersection_count < MAX_INTERSECTS)
		inter->intersection_count++;
	else
		return (true);
	inter->intersections[inter->intersection_count].t = (-vars[1] + sqrt(vars[3])) / (2 * vars[0]);
	if (inter->intersection_count < MAX_INTERSECTS)
		inter->intersection_count++;
	(void)cam;
	(void)minirt;
	return (true);
}

void	render_sphere(t_mlx *mlx, t_minirt *m)
{
	t_tuple			origin;
	int				i;
	int				j;
	int				pixel_num;
	int				wall_z;
	float			pixel_size;
	int				wall_size;
	float			half;
	t_intersects	*inter;
	t_sphere		*sphere;
	t_color			color;
	t_ray 			ray;

	i = -1;
	wall_size = 7;
	pixel_num = 1000;
	origin = return_tuple(0, 0, -6, 1);
	wall_z = 10;
	pixel_size = (float)wall_size / pixel_num;
	half = wall_size / 2;
	inter = ft_calloc(1, sizeof(t_intersects));
	inter->intersection_count = 0;
	ray.origin = return_tuple(origin.x, origin.y, origin.z, 1);
	sphere = create_sphere(0, 0, 0);
	color.colors = sphere->color;
	for (int k = 0; k < pixel_num; k++)
	{
		for (int l = 0; l < pixel_num; l++)
		{
			draw_pixel(mlx, l + 500, k + 50, 0x00ff00);
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	while (++i < pixel_num)
	{
		float world_i = half - pixel_size * i;
		j = -1;
		while (++j < pixel_num)
		{
			float world_j = half - pixel_size * j;
			t_tuple pos = return_tuple(world_j, world_i, wall_z, 1);
			//print_tuple_points(&pos);
			//ray.direction = subtract_tuples(&ray.origin, &pos);	// set ray direction
			ray.direction = subtract_tuples(&pos, &ray.origin);	// set ray direction
			t_bool hit = sphere_hit(m, NULL, inter, &ray, sphere);
			//t_bool hit = sphere_hit(m, NULL, inter, &ray, sphere);
			if (hit == true)
			if (best_hit(inter))
			{
				//best_hit(inter);
				draw_pixel(mlx, j + 500, i + 50, get_ray_color(&color));
			}
		}
	}
	printf("%d\n", inter->intersection_count);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
}

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

void	draw_circle(t_mlx *mlx, int originx, int originy, int radius)
{
	int e = -radius;
	int x = radius;
	int y = 0;
	while (y < x)
	{
		draw_pixel(mlx, originx + x, originy + y, 0xff0000);
		draw_pixel(mlx, originx - x, originy - y, 0xff0000);
		draw_pixel(mlx, originx + x, originy - y, 0xff0000);
		draw_pixel(mlx, originx - x, originy + y, 0xff0000);
		draw_pixel(mlx, originx + y, originy + x, 0xff0000);
		draw_pixel(mlx, originx - y, originy - x, 0xff0000);
		draw_pixel(mlx, originx - y, originy + x, 0xff0000);
		draw_pixel(mlx, originx + y, originy - x, 0xff0000);
		e += 2 * y + 1;
		y++;
		if (e >= 0)
		{
			e -= (2 * (x - 1));
			x--;
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
}

void	draw_background(t_mlx *mlx)
{
	int	i;
	int	j;

	i = -1;
	while (++i < HEIGHT - 1)
	{
		j = -1;
		while (++j < WIDTH - 1)
		{
			draw_pixel(mlx, j, i, 0x2f1221);
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
}

int main(void)
{
	t_minirt		*minirt;
	t_mlx			mlx;
	t_ray			*test;
	//t_ray			transformed_ray;
	//t_sphere		*sphere;
	t_intersects	*inter = NULL;

	init_mlx(&mlx);
	minirt = init_minirt(&mlx);
	test = create_ray(return_tuple(1, 2, 3, 1), return_tuple(0, 1, 0, 0));
	//sphere = create_sphere(0, 0, 0);
	inter = ft_calloc(1, sizeof(t_intersects));
	//sphere_hit(minirt, NULL, inter, test, sphere);
	//printf("intersect: %f\n", inter->intersections[0].t);
	//printf("intersect: %f\n", inter->intersections[1].t);
	draw_background(&mlx);
	render_sphere(&mlx, minirt);
	mlx_loop(mlx.mlx);
}

//#include <time.h>

//int main(void)
//{
//	t_intersects	inter;
//	srand(time(NULL));

//	ft_bzero(&inter, sizeof(t_intersects));
//	//for (int i = 0; i < 10; i++)
//	//{
//	//	inter.intersections[inter.intersection_count++].t = rand() % 50;
//	//	usleep(100);
//	//}
//	inter.intersections[inter.intersection_count++].t = 4;
//	inter.intersections[inter.intersection_count++].t = -6;
//	inter.intersections[inter.intersection_count++].t = -1;
//	inter.intersections[inter.intersection_count++].t = -12;
//	inter.intersections[inter.intersection_count++].t = -2;
//	inter.intersections[inter.intersection_count++].t = -5;
//	inter.intersections[inter.intersection_count++].t = -1;
//	inter.intersections[inter.intersection_count++].t = -214;
//	inter.intersections[inter.intersection_count++].t = -123;
//	inter.intersections[inter.intersection_count++].t = -90;
//	printf("Before sorting: \n");
//	for (int i = 0; i < 10; i++)
//		printf("%.2f\n", inter.intersections[i].t);
//	sort_intersects(&inter);
//	printf("After sorting: \n");
//	for (int i = 0; i < 10; i++)
//		printf("%.2f\n", inter.intersections[i].t);
//	printf("hit is: %f\n", best_hit(&inter));
//}