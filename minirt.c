/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/08/24 20:28:02 by pipolint         ###   ########.fr       */
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
	t_sphere	sphere;
	t_color		color;
	t_hit		hit;
	double		variables[4];
	double		disc;
	double		quad;

	sphere.color = malloc(sizeof(t_color));
	sphere.inward_normal = false;
	set_vector_points(&sphere.center, 0, 0, 0.012);
	//sphere.color->color.x = 0.94;
	//sphere.color->color.y = 0.39;
	//sphere.color->color.z = 0;
	sphere.radius = 0.5;
	set_vector_points(&hit.hit.origin, cam->camera.x, cam->camera.y, cam->camera.z);
	set_vector_points(&hit.hit.direction, ((double)j / WIDTH * 2 - 1) * cam->asp, ((double)i / HEIGHT * 2 - 1), cam->camera.z);
	normalize(&hit.hit.direction);
	variables[0] = dot_product(&hit.hit.direction, &hit.hit.direction);
	variables[1] = dot_product(&hit.hit.direction, &hit.hit.origin);
	variables[2] = dot_product(&hit.hit.origin, &hit.hit.origin) - sphere.radius * sphere.radius;
	disc = variables[1] * variables[1] - (variables[0] * variables[2]);
	if (disc < 0)
		return (false);
	variables[3] = sqrt(disc);
	quad = (variables[1] - variables[3]) / (variables[0]);
	if (quad >= T_MIN && quad <= T_MAX)
	{
		quad = ((variables[1] + variables[3]) / variables[0]);
		if (quad >= T_MAX || quad <= T_MIN)
			return (false);
	}
	sphere.hit.t = quad;
	sphere.hit.p = return_at(&hit.hit, sphere.hit.t);
	sphere.hit.normal = subtract_vectors(&sphere.center, &sphere.hit.p);
	normalize(&sphere.hit.normal);
	if (dot_product(&sphere.hit.normal, &hit.hit.direction) < 0)
		sphere.inward_normal = true;
	set_vector_points(&sphere.hit.normal, sphere.hit.normal.x, sphere.hit.normal.y, -sphere.hit.normal.z);
	color.color = sphere.hit.normal;
	draw_pixel(minirt->mlx, j, i, get_ray_color(&color));
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
		if(!fileopen(argv[1], minirt))
		{
			init_mlx(&mlx);
			render(&mlx, minirt);
				mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
			mlx_loop(mlx.mlx);
		}
		free(minirt);
	}
	else
		printf("Insufficient amount of arguments!\n");
}

