/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:40:13 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/21 10:42:33 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define YAW_SPEED 0.5
#define PITCH_SPEED 0.5
#define MOVE_SPEED 0.5

int	destroy(void *param)
{
	t_mlx	*mlx;

	mlx = param;
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
}

int	escape(int keycode, void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (keycode == ESC)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	return (1);
}

int	closert(t_minirt *m)
{
	printf("freeing things\n");
	free_things(m);
	(void)m;
	exit(0);
}

void	change_cammove(t_minirt *m)
{
	normalize(&m->forward);
	normalize(&m->up);
	normalize(&m->left);
	m->cam->view_matrix = view_transform_test(\
	&m->left, &m->from, &m->up, \
	&m->cam->trans, &m->forward);
}

void	camera_movement(t_minirt *m)
{
	t_bool		changed;

	if (m->movement.w == true)
	{
		m->cam->trans = add_vectors(&m->forward, &m->cam->trans);
		changed = true;
	}
	if (m->movement.s == true)
	{
		m->cam->trans = subtract_tuples(&m->forward, &m->cam->trans);
		changed = true;
	}
	if (m->movement.a == true)
	{
		m->cam->trans = subtract_tuples(&m->left, &m->cam->trans);
		changed = true;
	}
	if (m->movement.d == true)
	{
		m->cam->trans = add_vectors(&m->left, &m->cam->trans);
		changed = true;
	}
	if (changed == true)
		change_cammove(m);
}
