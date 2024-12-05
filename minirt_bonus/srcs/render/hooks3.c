/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:42:00 by ahaarij           #+#    #+#             */
/*   Updated: 2024/11/27 09:19:56 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_key_released(int keycode, t_minirt *m)
{
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
	return (0);
}

int	delta_time(void *param)
{
	static struct timespec	previous;
	t_minirt				*minirt;
	struct timespec			current;

	minirt = (t_minirt *)param;
	clock_gettime(CLOCK_MONOTONIC, &current);
	if (previous.tv_nsec != 0 || previous.tv_sec != 0)
	{
		minirt->delta_time = ((current.tv_sec - previous.tv_sec) \
		+ (current.tv_nsec - previous.tv_nsec) / 1e9f);
	}
	previous = current;
	threaded_render(minirt->mlx, minirt);
	return (0);
}

int	resetcam(t_minirt *m)
{
	m->cam->trans = m->original_from;
	m->forward = m->original_to;
	m->up = m->original_up;
	change_cammove(m);
	return (0);
}

int	closert(t_minirt *m)
{
	printf("freeing things\n");
	free_things(m);
	(void)m;
	exit(0);
}
