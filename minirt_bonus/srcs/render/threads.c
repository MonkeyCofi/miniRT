/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:31:46 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/10 19:01:56 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_threadhw(t_thread *s)
{
	s->height = HEIGHT / THREAD_NUM;
	s->width = WIDTH;
}

void	*render_part(void *thread)
{
	t_thread		*thr;
	t_ray			ray;
	t_tuple			c;
	t_tuple			color;

	thr = thread;
	set_threadhw(thr);
	thr->start_y = thr->height * thr->id;
	thr->end_y = (thr->start_y + thr->height);
	thr->start_x = 0;
	thr->end_x = thr->width;
	thr->i = thr->start_y - 1;
	while (++thr->i < thr->end_y)
	{
		thr->j = thr->start_x - 1;
		while (++thr->j < thr->end_x)
		{
			ray = ray_per_pixel(thr->camera, thr->j, thr->i);
			color = color_at(thr->minirt, &ray);
			return_color(color.x, color.y, color.z, &c);
			draw_pixel(thr->mlx, thr->j, thr->i, get_ray_color(&c));
		}
	}
	return (NULL);
}

void	puttext(t_minirt *minirt)
{
	char	*coord;
	char	*str;

	coord = ft_itoa(minirt->cam->trans.x);
	str = "Camera Coordinates - x : ";
	str = ft_strjoin(str, coord);
	str = ft_strjoin(str, " | y : ");
	coord = ft_itoa(minirt->cam->trans.y);
	str = ft_strjoin(str, coord);
	str = ft_strjoin(str, " | z : ");
	coord = ft_itoa(minirt->cam->trans.z);
	str = ft_strjoin(str, coord);
	mlx_string_put(minirt->mlx->mlx, minirt->mlx->win, 5, 10, 0x67FFFF, str);
	free(str);
}

int	threaded_render(t_mlx *mlx, t_minirt *minirt)
{
	pthread_t		threads[THREAD_NUM];
	t_thread		thr[THREAD_NUM];
	int				i;

	i = -1;
	ft_bzero(&thr, sizeof(t_thread));
	if (inverse_mat(&minirt->cam->view_matrix, &minirt->cam->inverse) \
	== false)
		return (-1);
	while (++i < THREAD_NUM)
	{
		thr[i].id = i;
		thr[i].camera = minirt->cam;
		thr[i].mlx = mlx;
		thr[i].minirt = minirt;
		pthread_create(&threads[i], NULL, render_part, &thr[i]);
	}
	i = -1;
	while (++i < THREAD_NUM)
		pthread_join(threads[i], NULL);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	puttext(minirt);
	return (1);
}
