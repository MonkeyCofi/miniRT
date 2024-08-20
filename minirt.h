/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:59:11 by pipolint          #+#    #+#             */
/*   Updated: 2024/08/20 19:27:50 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft/libft.h"
# include "mlx/mlx.h"
# include <math.h>

/*		temp headers	*/
# include <stdio.h>

# define PI 3.14159

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

typedef struct	s_color
{
	t_vector	color;
	double		alpha;
}	t_color;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}	t_ray;


typedef struct s_camera
{
	t_vector	camera;
	t_vector	v_horiz;
	t_vector	v_vert;
	double		focal_length;
	double		vh;
	double		vw;
	double		delta_vh;
	double		delta_vw;
	double		asp;
	double		fov;
}	t_camera;

// camera
t_camera	init_cam(void);

// hooks
int			escape(int keycode, void *param);

// vectors
t_vector	subtract_vectors(t_vector *vec1, t_vector *vec2);
void		set_vector_points(t_vector *v, double x, double y, double z);
double		dot_product(t_vector *vec1, t_vector *vec2);
void 		normalize(t_vector *vector);
t_vector	add_vectors(t_vector *vec1, t_vector *vec2);
void		scalar(t_vector *vec, double scalar);
t_vector	return_scalar(t_vector *vec, double scalar);

#endif