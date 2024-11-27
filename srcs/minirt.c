/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/27 10:27:49 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_shapes(t_minirt *minirt);

void	print_4d_points(double points[4][4])
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

t_minirt	*parse_objects(t_minirt *m)
{
	int	i;

	i = 0;
	while (i < m->object_count)
	{
		if (m->shapes[i]->type == SPHERE)
			init_sphere(m, &i);
		else if (m->shapes[i]->type == PLANE)
			init_plane(m, &i);
		else if (m->shapes[i]->type == CYLINDER)
			init_cylinder(m, &i);
		else if (m->shapes[i]->type == CONE)
			init_cone(m, &i);
	}
	return (m);
}

// int	test(int mouse_button, int mouse_x, int mouse_y, t_minirt *m)
// {
// 	t_ray			ray;
// 	t_intersects	intersect;
// 	t_intersection	*i;
// 	t_inter_comp	inter;

// 	ray = ray_per_pixel(m->cam, mouse_x, mouse_y);
// 	intersect = intersect_enivornment(m, &ray);
// 	i = best_hit(&intersect);
// 	inter = precompute_intersect(m, &intersect, i, &ray);
// 	// if (mouse_button == 1)
// 		// m->hooks.shape_or_cam = inter.obj;
// 	(void)mouse_button;
// 	(void)inter;
// 	return (1);
// }

double	deg_rad(double number)
{
	return (number * (PI / 180));
}

int	main(int ac, char **av)
{
	t_minirt		*m;

	if (ac == 2)
	{
		m = init_minirt();
		if (fileopen(av[1], m) == 1)
			return (1);
		if (m->object_count > 0)
			m = parse_objects(m);
		m->cam = return_camera_ptr(WIDTH, HEIGHT, deg_rad(m->cam->fov));
		m->cam->trans = m->from;
		m->forward = m->to;
		print_tuple_points(&m->left);
		m->cam->view_matrix = view_transform_test(&m->left, &m->up, \
		&m->cam->trans, &m->forward);
		// m->ppm = create_ppm("42_logo.ppm");
		m->original_from = return_point(m->from.x, m->from.y, m->from.z);
		m->original_to = return_point(m->to.x, m->to.y, m->to.z);
		m->original_up = return_vector(m->up.x, m->up.y, m->up.z);
		mlx_hook(m->mlx->win, 2, 1L << 0, get_key_pressed, m);
		mlx_hook(m->mlx->win, 3, 1L << 0, get_key_released, m);
		mlx_hook(m->mlx->win, 17, 1L << 2, closert, m);
		mlx_loop_hook(m->mlx->mlx, event_loop, m);
		mlx_loop(m->mlx->mlx);
	}
}
