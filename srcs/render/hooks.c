/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:40:13 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/04 13:16:28 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	// int i;
	// if(m->cam)
		// free cam func
	// if (m->lights)
	// 	free lights func
	// if (m->shapes)
		// free shapes func
	// ill do these once we merge the parsing tree cuz theres some more things to do :)
	(void)m;
	exit(0);
}

void	adjust_yaw(t_minirt *m, double angle)
 {
	double	old_x = m->to.x - m->from.x;
	double	old_z = m->to.z - m->from.z;

	m->to.x = old_x * cos(angle) - old_z * sin(angle) + m->from.x;
	m->to.z = old_x * sin(angle) + old_z * cos(angle) + m->from.z;
}

void    adjust_pitch(t_minirt *m, double angle)
{
	double	old_y = m->to.y - m->from.y;
	double	old_z = m->to.z - m->from.z;

	m->to.y = old_y * cos(angle) - old_z * sin(angle) + m->from.y;
	m->to.z = old_y * sin(angle) + old_z * cos(angle) + m->from.z;
}

void move_in_direction(t_minirt *m, t_tuple direction, float distance)
{
	m->from.x += direction.x * distance;
	m->from.y += direction.y * distance;
	m->from.z += direction.z * distance;

	m->to.x += direction.x * distance;
	m->to.y += direction.y * distance;
	m->to.z += direction.z * distance;
}


int get_key_pressed(int keycode, t_hook_params *hooks)
{
	t_minirt	*m = hooks->m;
	float		move_distance = 0.5;
	float		yaw_angle = 0.5;
	float		pitch_angle = 0.1; 
	t_tuple		right;
	t_tuple		forward = { 
	.x = m->to.x - m->from.x, 
	.y = m->to.y - m->from.y, 
	.z = m->to.z - m->from.z, 
	.w = m->to.w - m->from.w 
	};
	normalize(&forward);
	right = cross_product(&m->up, &forward);
	normalize(&right);
	if (keycode == W) 
	{
		move_in_direction(m, forward, move_distance);
		printf("W\n");
	}
	if (keycode == S)
	{
		move_in_direction(m, forward, -move_distance);
		printf("S\n");
	}
	if (keycode == A)
	{
		move_in_direction(m, right, -move_distance);
		printf("A\n");
	}
	if (keycode == D)
	{
		move_in_direction(m, right, move_distance);
		printf("D\n");
	}
	// found out rotations bymistake lmaoô
	if (keycode == LEFT)
	{
		adjust_yaw(m, yaw_angle);
		printf("LEFT\n");
	}
	if (keycode == RIGHT)
	{
		adjust_yaw(m, -yaw_angle);
		printf("RIGHT\n");
	}
	if (keycode == UP)
	{
		adjust_pitch(m, -pitch_angle);
		printf("UP\n");
	}
	if (keycode == DOWN)
	{
		adjust_pitch(m, pitch_angle);
		printf("DOWN\n");
	}
	if (keycode == R)
	{
		m->from = return_tuple(hooks->original_from.x, hooks->original_from.y, hooks->original_from.z, hooks->original_from.w);
		m->to = return_tuple(hooks->original_to.x, hooks->original_to.y, hooks->original_to.z, hooks->original_to.w);
		m->up = return_tuple(hooks->original_up.x, hooks->original_up.y, hooks->original_up.z, hooks->original_up.w);
	}
	if (keycode == E)
	{
		m->from.y += 0.5;
		m->to.y += 0.5;
	}
	if (keycode == Q)
	{
		m->from.y -= 0.5;
		m->to.y -= 0.5;
	}
	if (keycode == ESC)
		closert(hooks->m);
	m->cam->view_matrix = view_transform_test(&m->to, &m->from, &m->up);
	threaded_render(hooks->mlx, m);
	return (0);
}
