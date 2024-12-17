/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:40:13 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/10 18:53:13 by pipolint         ###   ########.fr       */
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

void	change_cammove(t_minirt *m)
{
	normalize(&m->forward);
	normalize(&m->up);
	normalize(&m->left);
	m->cam->view_matrix = view_transform(&m->left, &m->up, \
		&m->cam->trans, &m->forward);
}

t_bool	handle_w_s(t_minirt *m, t_tuple scaled_forward)
{
	if (m->movement.w == true)
	{
		m->cam->trans = add_vectors(&scaled_forward, &m->cam->trans);
		return (true);
	}
	if (m->movement.s == true)
	{
		m->cam->trans = subtract_tuples(&scaled_forward, &m->cam->trans);
		return (true);
	}
	return (false);
}

void	camera_movement(t_minirt *m)
{
	t_bool		changed;
	t_tuple		scaled_left;
	t_tuple		scaled_forward;

	scaled_forward = m->forward;
	scalar(&scaled_forward, 2);
	scaled_left = m->left;
	scalar(&scaled_left, 2);
	changed = false;
	if (m->movement.w == true || m->movement.s == true)
		changed = handle_w_s(m, scaled_forward);
	if (m->movement.a == true)
	{
		m->cam->trans = subtract_tuples(&scaled_left, &m->cam->trans);
		changed = true;
	}
	if (m->movement.d == true)
	{
		m->cam->trans = add_vectors(&scaled_left, &m->cam->trans);
		changed = true;
	}
	if (changed == true)
		change_cammove(m);
}
