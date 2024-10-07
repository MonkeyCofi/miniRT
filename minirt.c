/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/07 19:51:25 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	sort_intersects(t_intersects *intersects);
float	best_hit(t_intersects *intersects);

void	print_4d_points(float points[4][4])
{
	int	i;
	int	j;
	
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			printf("%.3f ", points[i][j]);
		printf("\n");
	}
}

t_tuple	*normal_pos(t_sphere *sphere, t_tuple pos)
{
	t_4dmat	*inverse_trans;
	t_tuple	*world_norm;
	t_tuple	sphere_norm;
	
	if (sphere->current_inverse)
		inverse_trans = sphere->current_inverse;
	else
	{
		if (inverse_mat(&sphere->transform, &inverse_trans) == error)
			return (NULL);
	}
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

	inverse_ray_mat = NULL;
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

t_4dmat	*view_transform(t_tuple *to, t_tuple *from, t_tuple *up)
{
	t_tuple	forward_vec;
	t_tuple	left_vec;
	t_tuple	real_up;
	t_4dmat	*orientation;
	t_4dmat	transl8;
	t_4dmat	*res;
	t_tuple	up_normalized;
	float	points[4][4] = {};
	
	forward_vec = subtract_tuples(from, to);
	up_normalized = return_tuple(up->x, up->y, up->z, VECTOR);
	normalize(&up_normalized);
	normalize(&forward_vec);
	left_vec = cross_product(&forward_vec, &up_normalized);
	real_up = cross_product(&left_vec, &forward_vec);
	points[0][0] = left_vec.x;
	points[0][1] = left_vec.y;
	points[0][2] = left_vec.z;
	points[1][0] = real_up.x;
	points[1][1] = real_up.y;
	points[1][2] = real_up.z;
	points[2][0] = -forward_vec.x;
	points[2][1] = -forward_vec.y;
	points[2][2] = -forward_vec.z;
	points[3][3] = 1;
	orientation = create_4dmat(points);
	transl8 = translation_mat(-from->x, -from->y, -from->z);
	res = mat4d_mult(orientation, &transl8);
	free(orientation);
	return (res);
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
	pixel_num = 800;
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
	sphere->material->color.colors = return_tuple(0.7, 0.3, 0.3, COLOR);
	light = create_light(return_tuple(1, 1, 1, COLOR), return_tuple(-10, -2, 0, POINT));
	transform_sphere(sphere, translate, return_tuple(-0.6, -0.9, 0, POINT));
	for (int k = 0; k < pixel_num; k++)
	{
		for (int l = 0; l < pixel_num; l++)
			draw_pixel(mlx, l + 500, k + 50, 69);
	}
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
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
}

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

t_inter_comp	*precompute_intersect(t_intersects *inter, t_intersection *intersection, t_ray *ray, t_sphere *sphere)
{
	t_inter_comp	*new;

	new = ft_calloc(1, sizeof(t_inter_comp));
	if (!new)
		return (NULL);
	new->eye_vec = return_tuple(-ray->direction.x, -ray->direction.y, -ray->direction.z, VECTOR);
	new->intersects = inter;
	new->t = intersection->t;
	//new->point = position(ray, inter->intersections[inter->intersection_count].t);
	new->point = position(ray, new->t);
	new->normal_vec = normal_pos(sphere, new->point);
	new->obj = sphere;
	if (dot_product(&new->eye_vec, new->normal_vec) < 0)
	{
		new->is_inside_object = true;
		negate(new->normal_vec);
	}
	else
		new->is_inside_object = false;
	return (new);
}

t_intersection	intersect(float t, t_shape_type type)
{
	t_intersection	intersection;

	intersection.t = t;
	intersection.type = type;
	return (intersection);
}

t_tuple	shade(t_minirt *minirt, t_inter_comp *intersect_comp)
{
	return (lighting(intersect_comp->obj->material, minirt->lights[0], intersect_comp->point, intersect_comp->eye_vec, *intersect_comp->normal_vec));
}

void	print_intersects(t_intersects *inter)
{
	for (int i = 0; i < inter->intersection_count; i++)
		printf("intersect[%d]: %f\n", i, inter->intersections[i].t);
}

t_intersects	*intersect_enivornment(t_mlx *mlx, t_minirt *minirt, t_ray *ray, t_sphere *sphere)
{
	t_intersects	*inter;
	//int				i;
	
	inter = ft_calloc(1, sizeof(t_intersects));
	if (sphere_hit(minirt, NULL, inter, ray, sphere, 1) == false)
	{
		printf("Sphere wasn't hit\n");
		return (inter);
	}
	print_intersects(inter);
	//i = -1;
	//while (++i < minirt->object_count)
	//{
	//	if (sphere_hit(minirt, NULL, inter, ray, minirt->spheres[i], 1) == false)
	//		continue ;
	//}
	sort_intersects(inter);
	(void)mlx;
	return (inter);
}

t_tuple	color_at(t_mlx *mlx, t_minirt *minirt, t_ray *ray, int i, t_sphere *sphere, t_intersection *intersection)
{
	t_intersects	*intersections;
	t_inter_comp	*computations;
	t_tuple			final_color;
	float			hit;

	intersections = intersect_enivornment(mlx, minirt, ray, sphere);
	hit = best_hit(intersections);
	printf("best hit: %f\n", hit);
	if (hit == -1)
		return (return_tuple(0, 0, 0, COLOR));
	//computations = precompute_intersect(intersections, &intersections->intersections[intersections->intersection_count], ray, minirt->spheres[i]);
	computations = precompute_intersect(intersections, intersection, ray, sphere);
	final_color = shade(minirt, computations);
	(void)i;
	return (final_color);
}

t_minirt	*init_default(t_mlx *mlx)
{
	t_minirt	*minirt;
	
	minirt = ft_calloc(1, sizeof(t_minirt));
	if (!minirt)
		return (NULL);
	minirt->spheres = ft_calloc(2, sizeof(t_sphere *));
	if (!minirt->spheres)
	{
		free(minirt);
		return (NULL);
	}
	minirt->lights = ft_calloc(1, sizeof(t_light *));
	if (!minirt->lights)
	{
		free(minirt->spheres);
		free(minirt);
		return (NULL);
	}
	
	/* LIGHT */
	minirt->lights[0] = ft_calloc(1, sizeof(t_light));
	if (!minirt->lights[0])
		return (NULL);
	minirt->lights[0]->intensity.colors = return_tuple(1, 1, 1, COLOR);
	minirt->lights[0]->position = return_tuple(-10, 10, -10, POINT);
	/* LIGHT */
	
	/* FIRST SPHERE */
	minirt->spheres[0] = ft_calloc(1, sizeof(t_sphere));
	if (!minirt->spheres[0])
		return (NULL);
	t_color	c;
	c.colors = return_tuple(0.8, 1, 0.6, COLOR);
	minirt->spheres[0]->material = create_material(c, 0.7, 0.1, 0.2, 200);
	minirt->spheres[0]->radius = 0.5;
	minirt->spheres[0]->center = return_tuple(0, 0, 0, POINT);
	/* FIRST SPHERE */
	
	/* SECOND SPHERE */
	minirt->spheres[1] = create_sphere(0, 0, 0, create_default_material());
	minirt->spheres[1]->radius = 1;
	minirt->spheres[1]->center = return_tuple(0, 0, 0, POINT);
	transform_sphere(minirt->spheres[1], scale, return_tuple(0.5, 0.5, 0.5, POINT));
	/* SECOND SPHERE */

	minirt->mlx = mlx;
	minirt->object_count = 2;
	return (minirt);
}

int main(void)
{
	t_minirt		*minirt;
	t_mlx			mlx;

	init_mlx(&mlx);
	//minirt = init_minirt(&mlx, 2, 1);
	minirt = init_default(&mlx);
	//t_ray *ray = create_ray(return_tuple(0, 0, -5, POINT), return_tuple(0, 0, 1, VECTOR));
	//intersect_enivornment(&mlx, minirt, ray);
	//t_tuple color = color_at(&mlx, minirt, ray, 0);
	//print_tuple_points(&color);
	render_sphere(&mlx, minirt);
	mlx_loop(mlx.mlx);
}

//int main(void)
//{
//	t_minirt		*rt;
//	t_intersection	i;
//	t_ray			*ray;
//	t_mlx			mlx;
//	t_intersects	*inter;
//	t_sphere		*sphere;
//	t_inter_comp	*computations;
	
//	init_mlx(&mlx);
//	rt = init_default(&mlx);
//	ray = create_ray(return_tuple(0, 0, -5, POINT), return_tuple(0, 0, 1, VECTOR));
//	inter = ft_calloc(1, sizeof(t_intersects));
//	sphere = create_sphere(0, 0, 0, create_default_material());
//	i = intersect(4, SPHERE);
//	computations = precompute_intersect(inter, &i, ray, sphere);
//	t_tuple color = color_at(&mlx, rt, ray, 0, sphere, &i);
//	print_tuple_points(&color);
//}

//int main(void)
//{
//	t_tuple to = return_tuple(0, 0, 0, POINT);
//	t_tuple from = return_tuple(0, 0, 8, POINT);
//	t_tuple up = return_tuple(0, 1, 0, VECTOR);
//	t_4dmat	*view = view_transform(&to, &from, &up);
//	print_4dmatrix(view);
//	t_4dmat trans = translation_mat(0, 0, -8);
//	printf("\n");
//	print_4dmatrix(&trans);
	
//}
