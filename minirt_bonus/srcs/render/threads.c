/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:31:46 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/26 10:51:48 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_threadhw(t_norm_thread *s)
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
	t_norm_thread	s;

	thr = thread;
	set_threadhw(&s);
	thr->start_y = s.height * thr->id;
	thr->end_y = (thr->start_y + s.height);
	thr->start_x = 0;
	thr->end_x = s.width;
	s.i = thr->start_y - 1;
	while (++s.i < thr->end_y)
	{
		s.j = thr->start_x - 1;
		while (++s.j < thr->end_x)
		{
			ray = ray_per_pixel(thr->camera, s.j, s.i);
			color = color_at(thr->minirt, &ray);
			return_color(color.x, color.y, color.z, &c);
			draw_pixel(thr->mlx, s.j, s.i, get_ray_color(&c));
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
	if (inverse_mat_test(&minirt->cam->view_matrix, &minirt->cam->inverse) \
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
