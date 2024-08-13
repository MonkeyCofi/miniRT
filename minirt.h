/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:59:11 by pipolint          #+#    #+#             */
/*   Updated: 2024/08/09 16:55:41 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft/libft.h"
# include "mlx/mlx.h"
# include <math.h>

/*		temp headers	*/
# include <stdio.h>

# ifdef __APPLE__
#  define HEIGHT 1080
#  define WIDTH 1920
#  define APPLE 1
#  define ESC 53
#  else
#  define HEIGHT 800
#  define WIDTH 1000
#  define APPLE 0
#  define ESC 65307
# endif

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

typedef struct	s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_camera
{
	t_vector	camera;
	t_vector	v_horiz;
	t_vector	v_vert;
	double		vh;
	double		vw;
	double		delta_vh;
	double		delta_vw;
	double		asp;
}	t_camera;

t_camera	init_cam(t_mlx *mlx);
void		set_vector_points(t_vector *v, double x, double y, double z);

#endif