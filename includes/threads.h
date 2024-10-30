/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:31:22 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/30 10:18:23 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H
# define THREADS_H

# include <pthread.h>
# include "structs.h"

typedef struct	s_thread
{
	t_minirt		*minirt;
	t_camera		*camera;
	t_mlx			*mlx;
	int				id;
	int				start_x;
	int				end_x;
	int				start_y;
	int				end_y;
}	t_thread;

# define THREAD_NUM 16

int	threaded_render(t_mlx *mlx, t_minirt *minirt, t_camera *camera);

#endif