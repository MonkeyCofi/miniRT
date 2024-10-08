/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_temp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:02:53 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/08 20:45:36 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
# define T_MIN (double)0.001
# define T_MAX (double)10000000

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
	int		i;
	int		j;
	float	a;

	i = -1;
	while (++i < HEIGHT - 1)
	{
		j = -1;
		while (++j < WIDTH - 1)
		{
			a = 0.5 * (i + 1);
			printf("%f\n", a);
		}
	}
	(void)mlx;
}

t_bool	sphere_hit(t_minirt *minirt, t_camera *cam, int i, int j)
{
	t_tuple		light;
	t_hit		hit;
	double		variables[4];
	double		disc;
	double		quad;

	minirt->spheres->inward_normal = false;
	set_vector_points(&hit.hit.origin, cam->camera.x, cam->camera.y, cam->camera.z);
	set_vector_points(&hit.hit.direction, ((double)j / WIDTH * 2 - 1) * cam->asp, ((double)i / HEIGHT * 2 - 1), cam->camera.z);
	set_vector_points(&light, 20, -1, -20);
	normalize(&light);
	normalize(&hit.hit.direction);
	variables[0] = dot_product(&hit.hit.direction, &hit.hit.direction);
	variables[1] = dot_product(&hit.hit.direction, &hit.hit.origin);
	variables[2] = dot_product(&hit.hit.origin, &hit.hit.origin) - minirt->spheres->radius * minirt->spheres->radius;
	disc = variables[1] * variables[1] - (variables[0] * variables[2]);
	if (disc < 0)
		return (false);
	variables[3] = sqrt(disc);
	quad = (variables[1] - variables[3]) / (variables[0]);
	if (quad <= T_MIN || T_MAX <= quad)
	{
		quad = ((variables[1] + variables[3]) / variables[0]);
		if (quad <= T_MIN || T_MAX <= quad)
			return (false);
	}
	minirt->spheres->hit.t = quad;
	minirt->spheres->hit.p = return_at(&hit.hit, minirt->spheres->hit.t);	// the point of intersection of the ray against the sphere
	minirt->spheres->hit.normal = subtract_tuples(&minirt->spheres->center, &minirt->spheres->hit.p);	// the normal at the point of intersection
	normalize(&minirt->spheres->hit.normal);
	if (dot_product(&minirt->spheres->hit.normal, &hit.hit.direction) < 0)
		minirt->spheres->inward_normal = true;
	t_tuple color;
	double	t;
	t = dot_product(&minirt->spheres->hit.normal, &light);
	color = return_scalar(&minirt->spheres->color, t);
	draw_pixel(minirt->mlx, j, i, get_ray_coloraarij(&color));
	return (true);
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
			sphere_hit(minirt, minirt->cam, 0);
			j++;
		}
		i++;
	}
	(void)mlx;
	(void)ray;
}

int main(int argc, char **argv)
{
	t_mlx		mlx;
	t_minirt	*minirt;
	
	if(argc == 2)
	{
		minirt = init_minirt(&mlx);
		if (!minirt)
			return (1);
		if(!fileopen(argv[1], minirt))
		{
			init_mlx(&mlx);
			render(&mlx, minirt);
			mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
			mlx_loop(mlx.mlx);
		}
		free(minirt->cam);
		free(minirt);
	}
	else
		printf("Insufficient amount of arguments!\n");
}


//void	render_sphere(t_mlx *mlx, t_minirt *m)
//{
//	t_tuple			origin;
//	int				i;
//	int				j;
//	int				pixel_num;
//	int				wall_z;
//	float			pixel_size;
//	int				wall_size;
//	float			half;
//	t_intersects	*inter;
//	t_sphere		*sphere;
//	t_color			color;
//	t_light			light;
//	t_ray 			ray;

//	i = -1;
//	wall_size = 7;
//	pixel_num = 1000;
//	origin = return_tuple(0, 0, -10, POINT);
//	wall_z = 10;
//	pixel_size = (float)wall_size / pixel_num;
//	half = wall_size / 2;
//	inter = ft_calloc(1, sizeof(t_intersects));
//	inter->intersection_count = 0;
//	ray.origin = return_tuple(origin.x, origin.y, origin.z, POINT);
//	sphere = create_sphere(0, 0, 0, NULL);
//	color.colors = sphere->color;
//	sphere->material = create_default_material();
//	sphere->material->color.colors = return_tuple(0.7, 0.3, 0.3, COLOR);
//	//light = create_light(return_tuple(1, 1, 1, COLOR), return_tuple(3, 5, 10, POINT));
//	light = create_light(return_tuple(1, 1, 1, COLOR), return_tuple(0, 3, 0, POINT));
//	//transform_sphere(sphere, translate, return_tuple(-0.6, -0.9, 0, POINT));
//	mlx_hook(mlx->win, 2, 0, get_key_pressed, sphere);
//	//if (keypress == 24)
//	//	transform_sphere(sphere, scale, return_tuple(2, 1, 0, POINT));
//	for (int k = 0; k < pixel_num; k++)
//	{
//		for (int l = 0; l < pixel_num; l++)
//			draw_pixel(mlx, l, k, 69);
//	}
//	while (++i < pixel_num)
//	{
//		float world_i = half - pixel_size * i;
//		j = -1;
//		while (++j < pixel_num)
//		{
//			float world_j = half - pixel_size * j;
//			t_tuple pos = return_tuple(world_j, world_i, wall_z, 1);
//			ray.direction = subtract_tuples(&pos, &ray.origin);	// set ray direction
//			normalize(&ray.direction);
//			t_bool hit = sphere_hit(m, NULL, inter, &ray, sphere, 1);
//			if (hit == true)
//			{
//				t_tuple point = position(&ray, inter->intersections[inter->intersection_count].t);
//				t_tuple	eye = return_tuple(ray.direction.x, ray.direction.y, ray.direction.z, VECTOR);
//				negate(&eye);
//				t_tuple *normal = normal_pos(sphere, point);
//				color.colors = lighting(sphere->material, &light, point, eye, *normal);
//				//draw_pixel(mlx, j + 500, i + 50, get_ray_color(&color));
//				draw_pixel(mlx, j, i, get_ray_color(&color));
//			}
//		}
//	}
//	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
//}

//t_inter_comp	*precompute_intersect(t_intersects *inter, t_ray *ray, t_sphere *sphere)
//{
//	t_inter_comp	*new;

//	new = ft_calloc(1, sizeof(t_inter_comp));
//	if (!new)
//		return (NULL);
//	new->eye_vec = return_tuple(-ray->direction.x, -ray->direction.y, -ray->direction.z, VECTOR);
//	new->intersects = inter;
//	new->t = inter->intersections[inter->intersection_count].t;
//	new->point = position(ray, inter->intersections[inter->intersection_count].t);
//	new->normal_vec = normal_pos(sphere, new->point);
//	new->obj = sphere;
//	if (dot_product(&new->eye_vec, new->normal_vec) < 0)
//	{
//		new->is_inside_object = true;
//		negate(new->normal_vec);
//	}
//	else
//		new->is_inside_object = false;
//	return (new);
//}