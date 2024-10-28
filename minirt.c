/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/28 10:39:13 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_shapes(t_minirt *minirt);

void	print_4d_points(double points[4][4])
{
	int	i;
	int	j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			printf("%.3f ", points[i][j]);
		printf("\n");
	}
}

int main(void)
{
	t_minirt		*m;
	t_mlx			mlx;
	t_4dmat			temp;
	t_hook_params	*hooks;

	hooks = ft_calloc(1, sizeof(t_hook_params));
	init_mlx(&mlx);
	m = init_default(&mlx);
	m->cam = return_camera_ptr(WIDTH, HEIGHT, PI / 3, NULL);
	m->from = return_tuple_pointer(0, 0.8, -20, POINT);
	m->to = return_tuple_pointer(0, 0, 0, POINT);
	m->up = return_tuple_pointer(0, 1, 0, VECTOR);
	m->cam->view_matrix = view_transform(m->to, m->from, m->up);
	// render(&mlx, m->cam, m);
	threaded_render(&mlx, m, m->cam);
	(void)temp;
	hooks->m = m;
	hooks->mlx = &mlx;
	hooks->original_from = return_point(m->from->x, m->from->y, m->from->z);
	hooks->original_to = return_point(m->to->x, m->to->y, m->to->z);
	hooks->original_up = return_vector(m->up->x, m->up->y, m->up->z);
	
	// I FUCKING COOKED HERE BRO WATCH THIS SHIT RIGHT HERE
	mlx_hook(mlx.win, 2, 1L << 0, get_key_pressed, hooks);
	mlx_hook(mlx.win, 17, 1L << 2, closert, m);
	mlx_loop(&mlx.mlx);
}
