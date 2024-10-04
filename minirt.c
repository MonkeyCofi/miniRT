/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/04 18:59:10 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	sort_intersects(t_intersects *intersects);
float	best_hit(t_intersects *intersects);

t_tuple	*normal_pos(t_sphere *sphere, t_tuple pos)
{
	t_4dmat	*inverse_trans;
	t_tuple	*object_point;
	t_tuple	*world_norm;
	t_tuple	sphere_norm;
	
	if (sphere->current_inverse)
		inverse_trans = sphere->current_inverse;
	else
	{
		if (inverse_mat(&sphere->transform, &inverse_trans) == error)
			return (NULL);
	}
	object_point = tuple_mult(inverse_trans, &pos);
	sphere_norm = subtract_tuples(&sphere->center, &pos);
	world_norm = tuple_mult(transpose(inverse_trans), &sphere_norm);
	normalize(world_norm);
	return (world_norm);
}
t_mater	*create_default_material()
{
	t_mater	*return_material;

	return_material = ft_calloc(1, sizeof(t_mater));
	if (!return_material)
		return (NULL);
	return_material->ambient = 0.1;
	return_material->diffuse = 0.9;
	return_material->specular = 0.9;
	return_material->shine = 200;
	return_material->color = return_color(1, 1, 1, 1);
	return (return_material);
}

t_mater	*create_material(t_color color, float diffuse, float ambient, float specular, float shine)
{
	t_mater	*ret_mat;

	ret_mat = ft_calloc(1, sizeof(t_mater));
	if (!ret_mat)
		return (NULL);
	ret_mat->color = color;
	ret_mat->diffuse = diffuse;
	ret_mat->ambient = ambient;
	ret_mat->specular = specular;
	ret_mat->shine = shine;
	return (ret_mat);
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

t_sphere	*create_sphere(float originx, float originy, float originz, t_mater *material)
{
	t_sphere	*ret;

	ret = ft_calloc(1, sizeof(t_sphere));
	if (!ret)
		return (NULL);
	ret->center = return_tuple(originx, originy, originz, 1);
	ret->color = return_tuple(0.8, 0.5, 0.3, 0);
	ret->radius = 1;
	ret->transform = identity();
	ret->current_inverse = NULL;
	if (material)
		ret->material = create_material(material->color, material->diffuse, material->ambient, material->specular, material->shine);
	else
		ret->material = create_material(return_color(1, 1, 1, 1), 0.9, 0.1, 0.9, 200);
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

t_bool	sphere_hit(t_minirt *minirt, t_camera *cam, t_intersects *inter, t_ray *ray, t_sphere *sphere, int with_transform)
{
	float	vars[4];
	t_tuple	sphere_dist;
	t_4dmat	*inverse_ray_mat;
	t_ray	*inverse_ray;
	t_tuple	*res;

	if (with_transform)
	{
		inverse_ray = create_ray(return_tuple(ray->origin.x, ray->origin.y, ray->origin.z, POINT), return_tuple(ray->direction.x, ray->direction.y, ray->direction.z, VECTOR));
		if (!sphere->current_inverse)
		{
			if (inverse_mat(&sphere->transform, &inverse_ray_mat) == error)
				return (error);
			if (!inverse_ray_mat)
				return (false);
			sphere->current_inverse = inverse_ray_mat;
			res = tuple_mult(inverse_ray_mat, &inverse_ray->origin);
			inverse_ray->origin = return_tuple(res->x, res->y, res->z, 1);
			res = tuple_mult(inverse_ray_mat, &inverse_ray->direction);
			inverse_ray->direction = return_tuple(res->x, res->y, res->z, 1);
		}
		else
		{
			res = tuple_mult(sphere->current_inverse, &inverse_ray->origin);
			inverse_ray->origin = return_tuple(res->x, res->y, res->z, 1);
			res = tuple_mult(sphere->current_inverse, &inverse_ray->direction);
			inverse_ray->direction = return_tuple(res->x, res->y, res->z, 1);
		}
		sphere_dist = subtract_tuples(&sphere->center, &inverse_ray->origin);
		vars[0] = dot_product(&inverse_ray->direction, &inverse_ray->direction);
		vars[1] = 2 * dot_product(&sphere_dist, &inverse_ray->direction);
	}
	else
	{
		sphere_dist = subtract_tuples(&sphere->center, &ray->origin);
		vars[0] = dot_product(&ray->direction, &ray->direction);
		vars[1] = 2 * dot_product(&sphere_dist, &ray->direction);
	}
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
	t_light			light;
	t_ray 			ray;

	i = -1;
	wall_size = 7;
	pixel_num = 700;
	origin = return_tuple(0, 0, -10, POINT);
	wall_z = 10;
	pixel_size = (float)wall_size / pixel_num;
	half = wall_size / 2;
	inter = ft_calloc(1, sizeof(t_intersects));
	inter->intersection_count = 0;
	ray.origin = return_tuple(origin.x, origin.y, origin.z, 1);
	sphere = create_sphere(0, 0, 0, NULL);
	color.colors = sphere->color;
	sphere->material = create_default_material();
	sphere->material->color.colors = return_tuple(1, 0.2, 1, COLOR);
	light = create_light(return_tuple(1, 1, 1, COLOR), return_tuple(-10, 0, 0, POINT));
	transform_sphere(sphere, translate, return_tuple(-0.5, -0.8, 0, POINT));
	//transform_sphere(sphere, scale, return_tuple(1, 0.5, 1, POINT));
	while (++i < pixel_num)
	{
		float world_i = half - pixel_size * i;
		j = -1;
		while (++j < pixel_num)
		{
			float world_j = half - pixel_size * j;
			t_tuple pos = return_tuple(world_j, world_i, wall_z, 1);
			ray.direction = subtract_tuples(&pos, &ray.origin);	// set ray direction
			normalize(&ray.direction);
			t_bool hit = sphere_hit(m, NULL, inter, &ray, sphere, 1);
			if (hit == true)
			{
				t_tuple point = position(&ray, inter->intersections[inter->intersection_count].t);
				t_tuple	eye = return_tuple(ray.direction.x, ray.direction.y, ray.direction.z, VECTOR);
				negate(&eye);
				t_tuple *normal = normal_pos(sphere, point);
				color.colors = lighting(sphere->material, &light, point, eye, *normal);
				draw_pixel(mlx, j + 500, i + 50, get_ray_color(&color));
			}
		}
	}
	for (int k = 0; k < inter->intersection_count; k++)
		printf("%d: %f\n", k, inter->intersections[k].t);
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

	init_mlx(&mlx);
	minirt = init_minirt(&mlx);
	//draw_background(&mlx);
	render_sphere(&mlx, minirt);
	mlx_loop(mlx.mlx);
}

//int main(void)
//{
//	t_tuple eyev = return_tuple(0, 0, -1, VECTOR);
//	t_tuple normal = return_tuple(0, 0, -1, VECTOR);
//	t_mater *m = create_default_material();
//	t_light light = create_light(return_tuple(1, 1, 1, COLOR), return_tuple(0, 0, -10, POINT));
//	t_tuple res = lighting(m, &light, return_tuple(0, 0, 0, POINT), eyev, normal);
//	print_tuple_points(&res);
//	free(m);
//}