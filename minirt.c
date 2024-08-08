/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/08/05 16:42:35 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

void	draw_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*p;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		 p = mlx->img.img_addr + (y * mlx->img.line_length) + (x * (mlx->img.bpp / 8));
		 *(unsigned int *)p = color;
	}
	return ;
}

int main(void)
{
	t_mlx	mlx;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "miniRT");
	mlx.img.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	mlx.img.img_addr = mlx_get_data_addr(mlx.img.img, &mlx.img.bpp, &mlx.img.line_length, &mlx.img.endian);
	if (!APPLE)
		mlx_hook(mlx.win, 2, 1L << 0, escape, &mlx);
	else
		mlx_hook(mlx.win, 2, 0, escape, &mlx);
	for (int i = 0; i < HEIGHT / 2; i++)
	{
		for (int j = 0; j < WIDTH / 2; j++)
		{
			draw_pixel(&mlx, j, i, 0xFFFFFFFF);
		}
	}
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
	mlx_loop(mlx.mlx);
}