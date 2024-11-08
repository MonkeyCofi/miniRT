/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:40:13 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/08 15:26:46 by pipolint         ###   ########.fr       */
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

int get_key_pressed(int keycode, t_hook_params *hooks)
{
	t_minirt	*m = hooks->m;
	// float		yaw_angle = 0.5;
	// float		pitch_angle = 0.1; 
	t_tuple		right;
	t_4dmat		rot;
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
		m->cam->trans = add_vectors(&forward, &m->cam->trans);
		printf("W\n");
	}
	if (keycode == S)
	{
		m->cam->trans = subtract_tuples(&forward, &m->cam->trans);
		printf("S\n");
	}
	if (keycode == A)
	{
		m->cam->trans = subtract_tuples(&right, &m->cam->trans);
		printf("A\n");
	}
	if (keycode == D)
	{
		m->cam->trans = add_vectors(&right, &m->cam->trans);
		printf("D\n");
	}
	if (keycode == LEFT)
	{
		rot = axis_angle(m->up, 0.5);
		matrix_cross(&forward, &forward, rot);
		normalize(&m->to);
		printf("LEFT\n");
	}
	if (keycode == RIGHT)
	{
		rot = axis_angle(m->up, -0.5);
		matrix_cross(&forward, &forward, rot);
		printf("RIGHT\n");
	}
	if (keycode == UP)
	{
		rot = axis_angle(right, 0.5);
		printf("UP\n");
	}
	if (keycode == DOWN)
	{
		rot = axis_angle(right, -0.5);
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
		m->cam->trans.y += 0.5;
	}
	if (keycode == Q)
	{
		m->cam->trans.y -= 0.5;
	}
	if (keycode == ESC)
		closert(hooks->m);
	m->cam->view_matrix = view_transform_test(&m->to, &m->from, &m->up, &m->cam->trans);
	threaded_render(hooks->mlx, m);
	return (0);
}


// int get_key_pressed(int keycode, t_hook_params *hooks)
// {
// 	t_minirt	*m = hooks->m;
// 	float		move_distance = 0.5;
// 	float		yaw_angle = 0.5;
// 	float		pitch_angle = 0.1; 
// 	t_tuple		right;
// 	t_tuple		forward = { 
// 	.x = m->to.x - m->from.x, 
// 	.y = m->to.y - m->from.y, 
// 	.z = m->to.z - m->from.z, 
// 	.w = m->to.w - m->from.w 
// 	};
// 	normalize(&forward);
// 	right = cross_product(&m->up, &forward);
// 	normalize(&right);
// 	if (keycode == W) 
// 	{
// 		move_in_direction(m, forward, move_distance);
// 		printf("W\n");
// 	}
// 	if (keycode == S)
// 	{
// 		move_in_direction(m, forward, -move_distance);
// 		printf("S\n");
// 	}
// 	if (keycode == A)
// 	{
// 		move_in_direction(m, right, -move_distance);
// 		printf("A\n");
// 	}
// 	if (keycode == D)
// 	{
// 		move_in_direction(m, right, move_distance);
// 		printf("D\n");
// 	}
// 	// found out rotations bymistake lmaoô
// 	if (keycode == LEFT)
// 	{
// 		adjust_yaw(m, yaw_angle);
// 		printf("LEFT\n");
// 	}
// 	if (keycode == RIGHT)
// 	{
// 		adjust_yaw(m, -yaw_angle);
// 		printf("RIGHT\n");
// 	}
// 	if (keycode == UP)
// 	{
// 		adjust_pitch(m, -pitch_angle);
// 		printf("UP\n");
// 	}
// 	if (keycode == DOWN)
// 	{
// 		adjust_pitch(m, pitch_angle);
// 		printf("DOWN\n");
// 	}
// 	if (keycode == R)
// 	{
// 		m->from = return_tuple(hooks->original_from.x, hooks->original_from.y, hooks->original_from.z, hooks->original_from.w);
// 		m->to = return_tuple(hooks->original_to.x, hooks->original_to.y, hooks->original_to.z, hooks->original_to.w);
// 		m->up = return_tuple(hooks->original_up.x, hooks->original_up.y, hooks->original_up.z, hooks->original_up.w);
// 	}
// 	if (keycode == E)
// 	{
// 		m->from.y += 0.5;
// 		m->to.y += 0.5;
// 	}
// 	if (keycode == Q)
// 	{
// 		m->from.y -= 0.5;
// 		m->to.y -= 0.5;
// 	}
// 	if (keycode == ESC)
// 		closert(hooks->m);
// 	m->cam->view_matrix = view_transform_test(&m->to, &m->from, &m->up);
// 	threaded_render(hooks->mlx, m);
// 	return (0);
// }
