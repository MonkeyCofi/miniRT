/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:40:13 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/20 18:19:30 by ahaarij          ###   ########.fr       */
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
	// int i;
	// if(m->cam)
		// free cam func
	// if (m->lights)
	// 	free lights func
	// if (m->shapes)
		// free shapes func
	// ill do these once we merge the parsing tree cuz theres some more things to do :)
	printf("freeing things\n");
	free_things(m);
	(void)m;
	exit(0);
}

void rebuild_camera_basis(t_tuple *forward, t_tuple *up, t_tuple *left)
{
	normalize(forward);
	if (is_equal(forward->x, 0) && is_equal(forward->z, 0))
		*left = return_vector(1, 0, 0);
	else{
		*left = cross_product(up, forward);
		normalize(left);
	}
	*up = cross_product(forward, left);
	normalize(up);
}

void	camera_movement(t_hook_params *hooks)
{
	t_minirt	*m = hooks->m;
	t_tuple		up;
	t_bool		changed;
	t_bool		sprint;
	up = return_vector(0,1,0);
	normalize(&m->forward);
	m->left = cross_product(&m->up, &m->forward);
	scalar(&m->forward, 4 * m->delta_time);
	normalize(&m->left);
	scalar(&m->left, 4 * m->delta_time);
	if (m->movement.sprint == true)
		sprint = true;
	if (m->movement.w == true) 
	{
		if(sprint == true)
			scalar(&m->forward, 2);
		m->cam->trans = add_vectors(&m->forward, &m->cam->trans);
		printf("W\n");
		sprint = false;
		changed = true;
	}
	if (m->movement.s == true)
	{
		if(sprint == true)
			scalar(&m->forward, 2);
		m->cam->trans = subtract_tuples(&m->forward, &m->cam->trans);
		printf("S\n");
		changed = true;
	}
	if (m->movement.a == true)
	{
		if (sprint == true)
			scalar(&m->left, 2);
		m->cam->trans = subtract_tuples(&m->left, &m->cam->trans);
		printf("A\n");
		changed = true;
	}
	if (m->movement.d == true)
	{
		if (sprint == true)
			scalar(&m->left, 2);
		m->cam->trans = add_vectors(&m->left, &m->cam->trans);
		printf("D\n");
		changed = true;
	}
	if (m->movement.space == true){
		m->cam->trans.y += 0.5;
		changed = true;
	}
	if (m->movement.shift == true){
		m->cam->trans.y -= 0.5;
		changed = true;
	}
	if(changed == true)
	{
		normalize(&m->forward);
		normalize(&m->up);
		normalize(&m->left);
		m->cam->view_matrix = view_transform_test(&m->left, &m->from, &m->up, &m->cam->trans, &m->forward);
	}
}

void	camera_rotation(t_hook_params *hooks)
{
	t_minirt	*m = hooks->m;
	t_4dmat		rot;
	t_bool		changed;
	normalize(&m->forward);
	m->left = cross_product(&m->up, &m->forward);
	normalize(&m->left);
	if (m->movement.left == true)
	{
		rot = y_rotation_mat(2 * m->delta_time);
		printf("LEFT\n");
		changed = true;
	}
	if (m->movement.right == true)
	{
		rot = y_rotation_mat(-2 * m->delta_time);
		printf("RIGHT\n");
		changed = true;
	}
	if (m->movement.up == true)
	{
		rot = axis_angle(m->left, 2 * m->delta_time);
		printf("UP\n");
		changed = true;
	}
	if (m->movement.down == true)
	{
		rot = axis_angle(m->left, -2 * m->delta_time);
		printf("DOWN\n");
		changed = true;
	}
	if(changed == true)
	{
		matrix_cross(&m->forward, &m->forward, rot);
		matrix_cross(&m->left, &m->left, rot);
		matrix_cross(&m->up, &m->up, rot);
		normalize(&m->left);
		m->left = cross_product(&m->up, &m->forward);
		normalize(&m->up);
		m->up = cross_product(&m->forward, &m->left);
		normalize(&m->forward);
		m->cam->view_matrix = view_transform_test(&m->left, &m->from, &m->up, &m->cam->trans, &m->forward);
		normalize(&m->forward);
		normalize(&m->up);
		normalize(&m->left);
	}
}

void	check_keycode(int keycode, t_minirt *m)
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
	if (keycode == 259)
		m->movement.sprint = true;
	if(keycode == R)
		m->movement.r = true;
	if (keycode == ESC)
		closert(m);
}

int get_key_pressed(int keycode, t_hook_params *hooks)
{
	t_minirt	*m = hooks->m;
	check_keycode(keycode, m);
	if(m->movement.up || m->movement.down || m->movement.right || m->movement.left)
		camera_rotation(hooks);
	if(m->movement.w || m->movement.a || m->movement.s || m->movement.d || m->movement.space || m->movement.shift)
		camera_movement(hooks);
	printf("%d\n", keycode);
	if (keycode == R)
	{
		m->cam->trans = hooks->original_from;
		m->forward = hooks->original_to;
		m->up = hooks->original_up;
		m->cam->view_matrix = view_transform_test(&m->left, &m->from, &m->up, &m->cam->trans, &m->forward);
	}
	if (keycode == ESC)
		closert(hooks->m);
	return (0);
}

int get_key_released(int keycode, t_hook_params *hooks)
{
	t_minirt *m = hooks->m;
	if (keycode == W)
		m->movement.w = false;
	if (keycode == A)
		m->movement.a = false;
	if (keycode == S)
		m->movement.s = false;
	if (keycode == D)
		m->movement.d = false;
	if (keycode == LEFT)
		m->movement.left = false;
	if (keycode == RIGHT)
		m->movement.right = false;
	if (keycode == UP)
		m->movement.up = false;
	if (keycode == DOWN)
		m->movement.down = false;
	if (keycode == 49)
		m->movement.space = false;
	if (keycode == 257)
		m->movement.shift = false;
	// if (keycode == 259)
	// 	m->movement.sprint = false;
	return (0);
}


int	delta_time(void *param)
{
	static struct timespec previous;
	t_minirt *minirt = (t_minirt *)param;
	struct timespec current;
	clock_gettime(CLOCK_MONOTONIC, &current);
	if(previous.tv_nsec != 0 || previous.tv_sec != 0)
	{
		minirt->delta_time = ((current.tv_sec - previous.tv_sec) + (current.tv_nsec - previous.tv_nsec) / 1e9f);
	}
	previous = current;
	threaded_render(minirt->mlx, minirt);
	return (0);
}

// int get_key_pressed(int keycode, t_hook_params *hooks)
// {
// 	t_minirt	*m = hooks->m;
// 	float		move_distance = 0.5;
// 	float		yaw_angle = 0.5;
// 	float		pitch_angle = 0.5; 
// 	t_tuple		m->left;
// 	t_tuple		forward = { 
// 	.x = m->to.x - m->from.x, 
// 	.y = m->to.y - m->from.y, 
// 	.z = m->to.z - m->from.z, 
// 	.w = m->to.w - m->from.w 
// 	};
// 	normalize(&forward);
// 	m->left = cross_product(&m->up, &forward);
// 	normalize(&m->left);
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
// 		move_in_direction(m, m->left, -move_distance);
// 		printf("A\n");
// 	}
// 	if (keycode == D)
// 	{
// 		move_in_direction(m, m->left, move_distance);
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
