/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:09:45 by pipolint          #+#    #+#             */
/*   Updated: 2024/09/27 17:55:39 by pipolint         ###   ########.fr       */
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

typedef union	u_tuple
{
	struct {
	float	x;
	float	y;
	float	z;
	float	w;
	};
	struct {
	float	r;
	float	g;
	float	b;
	float	a;
	};
}	t_tuple;

//typedef	struct s_matrix
//{
//	int		size;
//	float	**matrix;
//}	t_matrix;

typedef	struct s_3dmat
{
	float	m11;
	float	m12;
	float	m13;
	float	m21;
	float	m22;
	float	m23;
	float	m31;
	float	m32;
	float	m33;
}	t_3dmat;

typedef	struct	s_4dmat
{
	float	m11;
	float	m12;
	float	m13;
	float	m14;
	float	m21;
	float	m22;
	float	m23;
	float	m24;
	float	m31;
	float	m32;
	float	m33;
	float	m34;
	float	m41;
	float	m42;
	float	m43;
	float	m44;
}

typedef struct	s_color
{
	t_tuple	colors;
}	t_color;

typedef struct s_camera
{
	t_tuple	camera;
	t_tuple	orientation;
	t_tuple	v_horiz;
	t_tuple	v_vert;
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
	t_tuple	origin;
	t_tuple	direction;
}	t_ray;

typedef struct	s_hit
{
	t_ray		hit;
	t_tuple	p;
	t_tuple	normal;
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
	t_tuple	color;
	double		alpha;
	t_tuple	normal;
	t_tuple	center;
	t_hit		hit;
	double		radius;
	t_bool		inward_normal;
}	t_sphere;


typedef struct	s_shape
{
	s_shapes	shape;
	t_tuple	center;
	t_tuple	color;
	t_tuple	normal;
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