/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:31:22 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/10 17:32:34 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H
# define THREADS_H

# include <pthread.h>
# include "structs.h"

typedef struct s_thread
{
	t_minirt		*minirt;
	t_camera		*camera;
	t_bool			ready;
	t_mlx			*mlx;
	int				id;
	int				start_x;
	int				end_x;
	int				start_y;
	int				end_y;
	int				i;
	int				j;
	int				height;
	int				width;
}	t_thread;

# define THREAD_NUM 16

int	threaded_render(t_mlx *mlx, t_minirt *minirt);

#endif