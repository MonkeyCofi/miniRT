/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:01:16 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/14 17:20:53 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	*create_sphere(float originx, float originy, float originz, t_mater *material)
{
	t_sphere	*ret;

	ret = ft_calloc(1, sizeof(t_sphere));
	if (!ret)
		return (NULL);
	ret->center = return_tuple(originx, originy, originz, POINT);
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
t_bool	sphere_hit(t_minirt *minirt, t_camera *cam, t_intersects *inter, t_ray *ray, t_sphere *sphere, int with_transform)
{
	float	vars[4];
	t_tuple	sphere_dist;
	t_4dmat	*inverse_ray_mat;
	t_ray	*inverse_ray;
	t_tuple	*res;

	inverse_ray_mat = NULL;
	if (!sphere)
		return (false);
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
	if (inter->intersection_count < MAX_INTERSECTS)
	{
		inter->intersections[inter->intersection_count].t = (-vars[1] - sqrt(vars[3])) / (2 * vars[0]);
		inter->intersections[inter->intersection_count].shape = sphere;
		inter->intersections[inter->intersection_count].type = SPHERE;
		inter->intersections[inter->intersection_count].material = sphere->material;
		if (inter->intersection_count < MAX_INTERSECTS)
			inter->intersection_count++;
		else
			return (true);
	}
	if (inter->intersection_count < MAX_INTERSECTS)
	{
		inter->intersections[inter->intersection_count].t = (-vars[1] + sqrt(vars[3])) / (2 * vars[0]);
		inter->intersections[inter->intersection_count].shape = sphere;
		inter->intersections[inter->intersection_count].type = SPHERE;
		inter->intersections[inter->intersection_count].material = sphere->material;
		if (inter->intersection_count < MAX_INTERSECTS)
			inter->intersection_count++;
	}
	(void)cam;
	(void)minirt;
	return (true);
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
//	pixel_num = 500;
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
//	light = create_light(return_tuple(1, 1, 1, COLOR), return_tuple(0, 3, 0, POINT));
//	mlx_hook(mlx->win, 2, 0, get_key_pressed, sphere);
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
//				draw_pixel(mlx, j, i, get_ray_color(&color));
//			}
//		}
//	}
//	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
//}
