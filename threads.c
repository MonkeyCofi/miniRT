/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:31:46 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/24 21:35:22 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* 
	for every half of the width of the canvas
		for every half of the height of the canvas
			create a thread that will render that much pixels
			
*/

void	*render_part(void *thread)
{
	t_thread	*thr;
	t_ray		ray;
	t_color		c;
	t_tuple		color;
	int			height;
	int			width;
	int			i;
	int			j;

	thr = thread;
	height = HEIGHT / THREAD_NUM;
	width = WIDTH;
	thr->start_y = height * thr->id;
	thr->end_y = (thr->start_y + height);
	thr->start_x = 0;
	thr->end_x = width;
	i = thr->start_y - 1;
	while (++i < thr->end_y)
	{
		j = thr->start_x - 1;
		while (++j < thr->end_x)
		{
			ray = ray_per_pixel(thr->camera, j, i);
			color = color_at(thr->minirt, &ray);
			c.colors = return_color(color.x, color.y, color.z);
			draw_pixel(thr->mlx, j, i, get_ray_color(&c));
		}
	}
	return (NULL);
}

int	threaded_render(t_mlx *mlx, t_minirt *minirt, t_camera *camera)
{
	pthread_t		threads[THREAD_NUM];
	t_thread		thr[THREAD_NUM];
	int				i;

	i = -1;
	ft_bzero(&thr, sizeof(t_thread));
	if (inverse_mat(camera->view_matrix, &camera->inverse) == false)
		return (-1);
	while (++i < THREAD_NUM)
	{
		thr[i].id = i;
		thr[i].camera = camera;
		thr[i].mlx = mlx;
		thr[i].minirt = minirt;
		pthread_create(&threads[i], NULL, render_part, &thr[i]);
	}
	i = -1;
	while (++i < THREAD_NUM)
		pthread_join(threads[i], NULL);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	return (1);
}