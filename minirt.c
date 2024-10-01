/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/01 21:32:48 by pipolint         ###   ########.fr       */
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

float	possible_hit(t_intersects *intersects)
{
	int		i;
	float	ret;

	i = 0;
	ret = 0;
	while (i < intersects->int_num && intersects->int_num < 200)
	{
		//if (intersects->intersections[i].t)
		//	printf("hit %f\n", intersects->intersections[i].t);
		if (intersects->intersections[i].t > 0 && i != intersects->last_returned)
		{
			ret = intersects->intersections[i].t;
			intersects->last_returned = i;
		}
		else
			i++;
	}
	return (ret);
}

t_bool	sphere_hit(t_minirt *minirt, t_camera *cam, t_intersects *inter, t_ray *ray, t_sphere *sphere)
{
	float	vars[4];
	t_tuple	sphere_dist;
	
	sphere_dist = subtract_tuples(&ray->origin, &sphere->center);
	vars[0] = dot_product(&ray->direction, &ray->direction);
	vars[1] = 2 * dot_product(&ray->direction, &sphere_dist);
	vars[2] = dot_product(&sphere_dist, &sphere_dist) - sphere->radius * sphere->radius;
	//vars[3] = (vars[1] * vars[1]) - (4 * vars[0] * vars[2]);
	//printf("a %f b %f c %f determinant %f\n", vars[0], vars[1], vars[2], vars[3]);
	if (vars[3] < 0)
		return (false);
	//printf("%d\n", inter->int_num);
	inter->intersections[inter->int_num].t = (-vars[1] - sqrt(vars[3])) / (2 * vars[0]);
	if (inter->int_num < 200)
		inter->int_num++;
	else
		return (true);
	inter->intersections[inter->int_num].t = (-vars[1] + sqrt(vars[3])) / (2 * vars[0]);
	if (inter->int_num < 200)
		inter->int_num++;
	(void)cam;
	(void)minirt;
	return (true);
}

void	render_sphere(t_mlx *mlx, t_minirt *m)
{
	t_tuple	origin;
	int	i;
	int	j;
	int	pixel_num;
	int	wall_z;
	float	pixel_size;
	int	wall_size;
	float	half;
	t_intersects *inter;
	t_sphere	sphere;
	t_color		color;

	i = -1;
	wall_size = 7;
	pixel_num = 400;
	origin = return_tuple(0, 0, -5, 1);
	wall_z = 10;
	pixel_size = (float)wall_size / pixel_num;
	half = wall_size / 2;
	inter = ft_calloc(1, sizeof(t_intersects));
	t_ray ray;
	ray.origin = return_tuple(origin.x, origin.y, origin.z, 1);
	sphere.center = return_tuple(WIDTH / 2, HEIGHT / 2, 1, 1);
	sphere.radius = 3;
	sphere.color = return_tuple(0.2, 0.8, 0, 0);
	color.colors = sphere.color;
	while (++i < pixel_num)
	{
		float world_i = half - pixel_size * i;
		j = -1;
		while (++j < pixel_num)
		{
			float world_j = -half - pixel_size * j;
			t_tuple pos = return_tuple(world_j, world_i, wall_z, 1);
			ray.direction = subtract_tuples(&ray.origin, &pos);
			normalize(&ray.direction);
			//print_tuple_points(&ray.direction);
			sphere_hit(m, NULL, inter, &ray, &sphere);
			if (possible_hit(inter))
			{
				//printf("Hit\n");
				draw_pixel(mlx, j + (WIDTH / 2), i + (HEIGHT / 2), get_ray_color(&color));
			}
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
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

//void	render(t_mlx *mlx, t_minirt *minirt)
//{
//	int			i;
//	int			j;
//	t_ray		ray;

//	i = 0;
//	while (i < HEIGHT)
//	{
//		j = 0;
//		while (j < WIDTH)
//		{
//			sphere_hit(minirt, minirt->cam, 0);
//			j++;
//		}
//		i++;
//	}
//	(void)mlx;
//	(void)ray;
//}

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
	t_minirt	*minirt;
	t_mlx		mlx;

	init_mlx(&mlx);
	minirt = init_minirt(&mlx);
	//t_intersects *intersects = NULL;
	draw_background(&mlx);
	render_sphere(&mlx, minirt);
	//if (sphere_hit(minirt, NULL, 0, 0, &intersects) == error)
	//{
	//	write(2, "UwU\n", 4);
	//	return (1);
	//}
	//if (!intersects->intersections[0].t)
	//	printf("no intersects\n");
	//else
	//{
	//	printf("intersects[0]: %.3f\n", intersects->intersections[0].t);
	//	printf("Object at intersects[0] is a %s\n", intersects->intersections[0].type == SPHERE ? "Sphere" : "Other shape");
	//	printf("intersects[1]: %.3f\n", intersects->intersections[1].t);
	//	printf("Object at intersects[1] is a %s\n", intersects->intersections[1].type == SPHERE ? "Sphere" : "Other shape");
	//}
	mlx_loop(mlx.mlx);
}