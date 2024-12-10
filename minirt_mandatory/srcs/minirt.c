/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/10 15:49:10 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_key_pressed(int keycode, t_minirt *m)
{
	if (keycode == ESC)
		free_minirt(m, EXIT_SUCCESS);
	return (0);
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
	}
	return (m);
}

double	deg_rad(double number)
{
	return (number * (PI / 180));
}

static void	valid_dimensions(void)
{
	if (HEIGHT <= 0)
	{
		if (write(2, "Height cannot be lesser than or equal to zero!\n", 47) == -1)
			exit(EXIT_FAILURE);
		exit(EXIT_FAILURE);
	}
	if (WIDTH <= 0)
	{
		if (write(2, "Width cannot be lesser than or equal to zero!\n", 46) == -1)
			exit(EXIT_FAILURE);
		exit(EXIT_FAILURE);
	}
}

int	main(int ac, char **av)
{
	t_minirt		*m;

	valid_dimensions();
	if (ac == 2)
	{
		m = init_minirt(av[1]);
		init_mlx(m);
		if (fileopen(av[1], m) == 1)
			return (1);
		if (m->object_count > 0)
			m = parse_objects(m);
		m->cam = return_camera_ptr(WIDTH, HEIGHT, deg_rad(m->cam->fov));
		m->cam->trans = m->from;
		m->forward = m->to;
		m->cam->view_matrix = view_transform_test(&m->left, &m->up,
		&m->cam->trans, &m->forward);
		m->original_from = return_point(m->from.x, m->from.y, m->from.z);
		m->original_to = return_point(m->to.x, m->to.y, m->to.z);
		m->original_up = return_vector(m->up.x, m->up.y, m->up.z);
		mlx_hook(m->mlx->win, 2, 1L << 0, get_key_pressed, m);
		mlx_hook(m->mlx->win, 17, 1L << 2, closert, m);
		render(m->mlx, m->cam, m);
		mlx_loop(m->mlx->mlx);
	}
}
