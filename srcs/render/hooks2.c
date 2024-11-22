/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:40:33 by ahaarij           #+#    #+#             */
/*   Updated: 2024/11/22 01:03:23 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	camera_yaxis(t_minirt *m)
{
	t_bool	changed;

	if (m->movement.space == true)
	{
		m->cam->trans.y += 0.5;
		changed = true;
	}
	if (m->movement.shift == true)
	{
		m->cam->trans.y -= 0.5;
		changed = true;
	}
	if (changed == true)
		change_cammove(m);
}

void	change_camrot(t_minirt *m, t_4dmat rot)
{
	matrix_cross(&m->forward, &m->forward, rot);
	matrix_cross(&m->left, &m->left, rot);
	matrix_cross(&m->up, &m->up, rot);
	normalize(&m->left);
	m->left = cross_product(&m->up, &m->forward);
	normalize(&m->up);
	m->up = cross_product(&m->forward, &m->left);
	normalize(&m->forward);
	m->cam->view_matrix = view_transform_test(\
	&m->left, &m->from, &m->up, \
	&m->cam->trans, &m->forward);
	normalize(&m->forward);
	normalize(&m->up);
	normalize(&m->left);
}

void	camera_rotation(t_minirt *m)
{
	t_4dmat		rot;
	t_bool		changed;

	if (m->movement.left == true)
	{
		rot = y_rotation_mat(2 * m->delta_time);
		changed = true;
	}
	if (m->movement.right == true)
	{
		rot = y_rotation_mat(-2 * m->delta_time);
		changed = true;
	}
	if (m->movement.up == true)
	{
		rot = axis_angle(m->left, 2 * m->delta_time);
		changed = true;
	}
	if (m->movement.down == true)
	{
		rot = axis_angle(m->left, -2 * m->delta_time);
		changed = true;
	}
	// if(m->movement.r == true)
	if (changed == true)
		change_camrot(m, rot);
}

int	get_key_pressed(int keycode, t_minirt *m)
{
	if (keycode == W)
		m->movement.w = true;
	if (keycode == A)
		m->movement.a = true;
	if (keycode == S)
		m->movement.s = true;
	if (keycode == D)
		m->movement.d = true;
	if (keycode == LEFT)
		m->movement.left = true;
	if (keycode == RIGHT)
		m->movement.right = true;
	if (keycode == UP)
		m->movement.up = true;
	if (keycode == DOWN)
		m->movement.down = true;
	if (keycode == 49)
		m->movement.space = true;
	if (keycode == 257)
		m->movement.shift = true;
	if (keycode == R)
		m->movement.r = true;
	if (keycode == ESC)
		closert(m);
	return (0);
}

int	event_loop(t_minirt *m)
{
	if (m->movement.up || m->movement.down
		|| m->movement.right || m->movement.left || m->movement.r)
	{
		normalize(&m->forward);
		m->left = cross_product(&m->up, &m->forward);
		normalize(&m->left);
		camera_rotation(m);
	}
	if (m->movement.w || m->movement.a || m->movement.s
		|| m->movement.d || m->movement.space || m->movement.shift)
	{
		normalize(&m->forward);
		m->left = cross_product(&m->up, &m->forward);
		scalar(&m->forward, 4 * m->delta_time);
		normalize(&m->left);
		scalar(&m->left, 4 * m->delta_time);
		if (m->movement.space || m->movement.shift)
			camera_yaxis(m);
		else
			camera_movement(m);
	}
	delta_time(m);
	return (0);
}
