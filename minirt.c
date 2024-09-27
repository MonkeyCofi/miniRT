/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/09/27 17:57:13 by pipolint         ###   ########.fr       */
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

t_bool	sphere_hit(t_minirt *minirt, t_camera *cam, int i, int j)
{
	t_tuple	light;
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
	negate(&light);
	//light.x *= -1;
	minirt->spheres->hit.t = quad;
	minirt->spheres->hit.p = return_at(&hit.hit, minirt->spheres->hit.t);	// the point of intersection of the ray against the sphere
	minirt->spheres->hit.normal = subtract_tuples(&minirt->spheres->center, &minirt->spheres->hit.p);	// the normal at the point of intersection
	normalize(&minirt->spheres->hit.normal);
	if (dot_product(&minirt->spheres->hit.normal, &hit.hit.direction) < 0)
		minirt->spheres->inward_normal = true;
	t_tuple color;
	double	t;
	t = dot_product(&minirt->spheres->hit.normal, &light);
	color = return_scalar(&minirt->spheres->color, -t);
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
//				mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
//			mlx_loop(mlx.mlx);
//		}
//		free(minirt->cam);
//		free(minirt);
//	}
//	else
//		printf("Insufficient amount of arguments!\n");
//}

/* =============================Test Main============================= */

int main(void)
{
	t_tuple test;
	t_tuple test2;

	set_point_points(&test, 3, 2, 1);
	set_point_points(&test2, 5, 6, 7);
	t_tuple res = subtract_tuples(&test2, &test);
	print_tuple_points(&res);
	printf("Resultant tuple is a vector: %s\n", is_vector(&res) ? "True" : "False");
	printf("Resultant tuple is a point: %s\n", is_point(&res) ? "True" : "False");

	printf("\n==============================\n\n");

	set_vector_points(&test, 1, 2, 3);
	set_point_points(&test2, 5, 6, 7);
	negate(&test);
	print_tuple_points(&test);
	printf("Resultant tuple is a vector: %s\n", is_vector(&test) ? "True" : "False");
	printf("Resultant tuple is a point: %s\n", is_point(&test) ? "True" : "False");
	
	printf("\n==============================\n\n");
	
	t_tuple	mag_test;
	set_vector_points(&mag_test, -1, -2, -3);
	printf("The magnitude is: %.5f\n", magnitude(&mag_test));
	
	printf("\n==============================\n\n");
	
	t_tuple	normalize_test;
	set_vector_points(&normalize_test, 1, 2, 3);
	normalize(&normalize_test);
	print_tuple_points(&normalize_test);
	printf("The magnitude of the normalized vector is: %.5f\n", magnitude(&normalize_test));
	
	printf("\n==============================\n\n");
	
	float diff = 0.000101512;
	printf("%.10f\n", diff);
	printf("\n=====Loop=====\n");
	float n = 0.1;
	for (int i = 0; i < 5; i++)
	{
		if (is_equal(n, diff))
		{
			printf("Floats are equal\n");
			break ;	
		}
		printf("%.10f\n", n);
		n /= 10;
	}
	printf("%.10f\n", n);
	
	printf("\n==============================\n\n");

}

/* =============================Test Main============================= */