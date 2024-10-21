/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:09:45 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/21 21:02:52 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdlib.h>
# include "../libft/libft.h"

# define MAX_INTERSECTS 200
# define VECTOR 0
# define POINT 1
# define COLOR 1

typedef struct s_intersects t_intersects;
typedef struct s_minirt t_minirt;

typedef enum e_bool
{
	false,
	true,
	error
}	t_bool;

typedef enum e_trans
{
	scale,
	rotate_x,
	rotate_y,
	rotate_z,
	translate,
	none
}	t_trans;

typedef enum e_shapes
{
	SPHERE,
	CYLINDER,
	PLANE,
	CONE
}	t_shape_type;

typedef union u_tuple
{
	struct
	{
		float	x;
		float	y;
		float	z;
		float	w;
	};
	struct
	{
		float	r;
		float	g;
		float	b;
		float	a;
	};
}	t_tuple;

typedef union u_2dmat
{
	struct
	{
		float	m11;
		float	m12;
		float	m21;
		float	m22;
	};
	float	matrix[2][2];
}	t_2dmat;

typedef union u_3dmat
{
	struct
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
	};
	float	matrix[3][3];
}	t_3dmat;

typedef union u_4dmat
{
	struct
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
	};
	float	matrix[4][4];
}	t_4dmat;

typedef struct s_color
{
	t_tuple	colors;
}	t_color;

typedef struct s_camera
{
	t_4dmat	*view_matrix;
	t_4dmat	*inverse;
	float	horizontal_canv_size;
	float	vertical_canv_size;
	float	pixel_size;
	float	fov;
	float	aspect;
	float	half_view;
	float	half_width;
	float	half_height;
}	t_camera;

typedef struct s_ray
{
	t_tuple	origin;
	t_tuple	direction;
}	t_ray;

typedef struct	s_mater
{
	t_color	color;
	float	ambient;
	float	specular;
	float	diffuse;
	float	shine;
}	t_mater;

typedef struct s_shape
{
	t_shape_type	type;
	void			*shape;
	t_ray			*inverse_ray;
	t_4dmat			transform;
	t_4dmat			*inverse_mat;
	t_4dmat			*inverse_transpose;
	t_mater			*material;
	t_tuple			*(*normal)(struct s_shape *, t_tuple);
	t_bool			(*intersect)(t_minirt *, t_intersects *, t_ray *, int);
}	t_shape;

typedef struct s_intersection
{
	float			t;
	t_shape			*shape_ptr;
	void			*shape;
	t_mater			*material;
	t_shape_type	type;
}	t_intersection;

typedef struct s_intersects
{
	int				intersection_count;
	int				last_intersection;
	t_intersection	intersections[MAX_INTERSECTS];
}	t_intersects;

typedef struct s_img
{
	void	*img;
	char	*img_addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
}	t_mlx;

typedef struct s_hit
{
	t_ray		hit;
	t_tuple		p;
	t_tuple		normal;
	t_shape		shape;
	float		t;
}	t_hit;

typedef struct s_sphere
{
	t_tuple		color;
	t_tuple		normal;
	t_tuple		center;
	t_4dmat		transform;
	t_4dmat		*current_inverse;
	t_mater		*material;
	t_bool		inward_normal;
	t_hit		hit;
	float		alpha;
	float		radius;
	float		diameter;
}	t_sphere;

typedef struct	s_plane
{
	t_tuple	point;
	t_tuple	normal;
	t_mater	*material;
	t_4dmat	*inverse;
	t_4dmat	transform;
}	t_plane;

typedef struct	s_light
{
	t_color	intensity;
	t_tuple	position;
}	t_light;

typedef struct	s_cylinder
{
	float			radius;
	t_tuple			orientation;
	t_tuple			point;
	t_tuple			normal;
	t_mater			*material;
	t_4dmat			transform;
	t_4dmat			*inverse;
	t_bool			is_closed;
	float			minimum;
	float			maximum;
	t_shape_type	type;
}	t_cylinder;

typedef struct	s_cone
{
	float			radius;
	float			minimum;
	float			maximum;
	t_bool			is_closed;
	t_tuple			point;
	t_4dmat			transform;
	t_4dmat			*inverse;
	t_mater			*material;
	t_shape_type	type;
}	t_cone;

typedef struct	s_inter_comp
{
	t_intersects	*intersects;
	t_shape_type	type;
	t_tuple			normal_vec;
	t_shape			*obj;
	t_mater			*material;
	t_tuple			point;
	t_tuple			eye_vec;
	t_bool			is_inside_object;
	float			t;
}	t_inter_comp;

typedef struct s_minirt
{
	t_mlx		*mlx;
	t_camera	*cam;
	t_sphere	**spheres;
	t_shape		**shapes;
	t_light		**lights;
	t_plane		*plane;
	int			object_count;
	int			light_count;
}	t_minirt;

#endif