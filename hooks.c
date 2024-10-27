/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:40:13 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/27 18:30:28 by ahaarij          ###   ########.fr       */
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

void	adjust_yaw(t_minirt *m, int i)
{
	float old_x;
	float old_z;

	if(i == 0)
	{
		old_x = m->to->x - m->from->x;
		old_z = m->to->z - m->from->z;

		m->to->x = old_x * cos(0.25) - old_z * sin(0.25) + m->from->x;
		m->to->z = old_x * sin(0.25) + old_z * cos(0.25) + m->from->z;
	}
	if(i == 1)
	{
		old_x = m->to->x - m->from->x;
		old_z = m->to->z - m->from->z;
	
		m->to->x = old_x * cos(-0.25) - old_z * sin(-0.25) + m->from->x;
		m->to->z = old_x * sin(-0.25) + old_z * cos(-0.25) + m->from->z;
	}
}

void    adjust_pitch(t_minirt *m, int i)
{
	float	old_z;
	float	old_y;
    float	angle = 0.1; // easier to just yk, adjust once instead of all of em

	if (i == 0)
	{
		old_y = m->to->y - m->from->y;
		old_z = m->to->z - m->from->z;
		m->to->y = old_y * cos(angle) + old_z * sin(angle) + m->from->y;
		m->to->z = -old_y * sin(angle) + old_z * cos(angle) + m->from->z;
	}
	if (i == 1)
	{
		old_y = m->to->y - m->from->y;
		old_z = m->to->z - m->from->z;
		m->to->y = old_y * cos(angle) - old_z * sin(angle) + m->from->y;
		m->to->z = old_y * sin(angle) + old_z * cos(angle) + m->from->z;
	}       
}

int get_key_pressed(int keycode, t_hook_params *hooks)
{
	// I FUCKING COOKED HOLY SHIT IM SO CRAAACKKEEDDDD
	t_minirt *m = hooks->m; 
	if (keycode == W) 
	{
		m->from->z += 0.5;
		m->to->z += 0.5;
		printf("W\n");
	}
	if (keycode == S)
	{
		m->from->z -= 0.5;
		m->to->z -= 0.5;
		printf("S\n");
	}
	if (keycode == A)
	{
		m->from->x -= 0.5;
		m->to->x -= 0.5;
		printf("A\n");
	}
	if (keycode == D)
	{
		m->from->x += 0.5;
		m->to->x += 0.5;
		printf("D\n");
	}
	// found out rotations bymistake lmaoô
	if (keycode == LEFT)
	{
		adjust_yaw(m, 0);
		printf("LEFT\n");
	}
	if (keycode == RIGHT)
	{
		adjust_yaw(m, 1);
		printf("RIGHT\n");
	}
	if (keycode == UP)
	{
		adjust_pitch(m, 0);
		printf("UP\n");
	}
	if (keycode == DOWN)
	{
		adjust_pitch(m, 1);
		printf("DOWN\n");
	}
	if (keycode == R)
	{
		m->from = return_tuple_pointer(hooks->original_from.x, hooks->original_from.y, hooks->original_from.z, hooks->original_from.w);
		m->to = return_tuple_pointer(hooks->original_to.x, hooks->original_to.y, hooks->original_to.z, hooks->original_to.w);
		m->up = return_tuple_pointer(hooks->original_up.x, hooks->original_up.y, hooks->original_up.z, hooks->original_up.w);
	}
	if (keycode == E)
	{
		m->from->y += 0.5;
		m->to->y += 0.5;
	}
	if (keycode == Q)
	{
		m->from->y -= 0.5;
		m->to->y -= 0.5;
	}
	if (keycode == ESC)
		closert(hooks->m);
	m->cam->view_matrix = view_transform(m->to, m->from, m->up);
	threaded_render(hooks->mlx, m, hooks->m->cam);
	return (0);
}