/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/08/28 17:11:13 by pipolint         ###   ########.fr       */
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
	t_vector	light;
	t_hit		hit;
	double		variables[4];
	double		disc;
	double		quad;

	minirt->spheres->inward_normal = false;
	set_vector_points(&hit.hit.origin, cam->camera.x, cam->camera.y, cam->camera.z);
	set_vector_points(&hit.hit.direction, ((double)j / WIDTH * 2 - 1) * cam->asp, ((double)i / HEIGHT * 2 - 1), cam->camera.z);
	set_vector_points(&light, -1, -1, -1);
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
	light.x *= -1;
	minirt->spheres->hit.t = quad;
	minirt->spheres->hit.p = return_at(&hit.hit, minirt->spheres->hit.t);	// the point of intersection of the ray against the sphere
	minirt->spheres->hit.normal = subtract_vectors(&minirt->spheres->center, &minirt->spheres->hit.p);	// the normal at the point of intersection
	normalize(&minirt->spheres->hit.normal);
	if (dot_product(&minirt->spheres->hit.normal, &hit.hit.direction) < 0)
		minirt->spheres->inward_normal = true;
	t_vector color;
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
			//if (hit)
			//	draw_pixel(mlx, j, i, 0xf0f0f0);
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

