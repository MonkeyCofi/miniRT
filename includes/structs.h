/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:09:45 by pipolint          #+#    #+#             */
/*   Updated: 2024/08/25 21:31:28 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum	e_bool
{
	false,
	true
}	t_bool;

typedef enum	e_shapes
{
	SPHERE,
}	s_shapes;

typedef struct	s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct	s_color
{
	t_vector	colors;
	double		alpha;
}	t_color;

typedef struct s_camera
{
	t_vector	camera;
	t_vector	orientation;
	t_vector	v_horiz;
	t_vector	v_vert;
	double		focal_length;
	double		vh;
	double		vw;
	double		delta_vh;
	double		delta_vw;
	double		asp;
	int			h_fov;
	int			v_fov;
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
	t_vector	color;
	double		alpha;
	t_vector	normal;
	t_vector	center;
	t_hit		hit;
	double		radius;
	t_bool		inward_normal;
}	t_sphere;


typedef struct	s_shape
{
	s_shapes	shape;
	t_vector	center;
	t_vector	color;
	t_vector	normal;
	t_hit		hit;
	t_bool		inward_normal;
	double		alpha;
}	t_shape;

typedef struct s_minirt
{
	t_mlx		*mlx;
	t_camera	*cam;
	t_sphere	*spheres;
	t_shape		*shapes;
}	t_minirt;


#endif