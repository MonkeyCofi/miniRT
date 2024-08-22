/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:13:37 by pipolint          #+#    #+#             */
/*   Updated: 2024/08/21 16:13:55 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MLX_H
# define MY_MLX_H

typedef struct s_img
{
	void	*img;
	char	*img_addr;
	int		bpp;
	int		line_length;
	int		endian;
}		t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
}	t_mlx;

#endif