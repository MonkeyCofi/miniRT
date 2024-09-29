/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/09/29 18:30:58 by pipolint         ###   ########.fr       */
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
	float points[4][4];
	points[0][0] = 3; 
	points[0][1] = -9; 
	points[0][2] = 7;
	points[0][3] = 3;
	points[1][0] = 3; 
	points[1][1] = -8; 
	points[1][2] = 2;
	points[1][3] = -9;
	points[2][0] = -4; 
	points[2][1] = 4; 
	points[2][2] = 4;
	points[2][3] = 1;
	points[3][0] = -6;
	points[3][1] = 5; 
	points[3][2] = -1;
	points[3][3] = 1;
	t_4dmat *mat_a = create_4dmat(points);
	points[0][0] = 8; 
	points[0][1] = 2; 
	points[0][2] = 2;
	points[0][3] = 2;
	points[1][0] = 3; 
	points[1][1] = -1; 
	points[1][2] = 7;
	points[1][3] = 0;
	points[2][0] = 7; 
	points[2][1] = 0; 
	points[2][2] = 5;
	points[2][3] = 4;
	points[3][0] = 6;
	points[3][1] = -2; 
	points[3][2] = 0;
	points[3][3] = 5;
	t_4dmat *mat_b = create_4dmat(points);
	t_4dmat *prod = mat4d_mult(mat_a, mat_b);
	printf("Matrix A: \n");
	print_4dmatrix(mat_a);
	printf("\n");
	printf("Matrix B: \n");
	print_4dmatrix(mat_b);
	printf("\n");
	printf("A * B: \n");
	print_4dmatrix(prod);
	printf("\n");
	printf("Inverse of Matrix B: \n");
	t_4dmat *inv;
	if (inverse_mat(mat_b, &inv) == false)
		return (1);
	print_4dmatrix(inv);
	printf("\n");
	t_4dmat *orig = mat4d_mult(prod, inv);
	printf("Product * inverse of B: \n");
	print_4dmatrix(orig);
	free(mat_a);
	free(mat_b);
	free(prod);
}

/* =============================Test Main============================= */