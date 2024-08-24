/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:09:45 by pipolint          #+#    #+#             */
/*   Updated: 2024/08/24 18:22:49 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum	e_bool
{
	false,
	true
}	t_bool;

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

typedef struct s_camera
{
	t_vector	camera;
	t_vector	orientation;
	t_vector	v_horiz;
	t_vector	v_vert;
	t_vector	first_pixel;
	double		focal_length;
	double		vh;
	double		vw;
	double		delta_vh;
	double		delta_vw;
	double		asp;
	int			fov;
	t_bool		flag;
}	t_camera;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}	t_ray;

typedef struct	s_hit
{
	t_ray		hit;
	t_vector	p;
	t_vector	normal;
	double		t;
}	t_hit;

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

typedef struct	s_sphere
{
	t_color		*color;
	t_vector	normal;
	t_vector	center;
	double		radius;
	t_hit		hit;
}	t_sphere;

typedef struct s_minirt
{
	t_mlx		*mlx;
	t_camera	*cam;
	t_sphere	*spheres;
}	t_minirt;


#endif