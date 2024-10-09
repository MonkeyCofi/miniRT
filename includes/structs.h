/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:09:45 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/09 19:38:35 by pipolint         ###   ########.fr       */
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
	PLANE
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

/* NOT IN USE: POTENTIAL MATRIX TAGGED UNION*/

typedef	enum e_matsize
{
	MAT2D,
	MAT3D,
	MAT4D
}	t_matsize;

typedef struct s_matrix
{
	t_matsize	mat_type;
	union u_mat2d
	{
		struct
		{
			float	m11;
			float	m12;
			float	m21;
			float	m22;	
		};
		float	matrix[2][2];
	}	t_mat2d;
	union u_mat3d
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
	}	t_mat3d;
	union u_mat4d
	{
		struct s_mat4
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
		}	t_mat4;
		float	matrix[4][4];
	}	t_mat4d;
}	t_matrix;

/* NOT IN USE: POTENTIAL MATRIX TAGGED UNION*/

typedef struct s_color
{
	t_tuple	colors;
}	t_color;

//typedef struct s_camera
//{
//	t_tuple	camera;
//	t_tuple	orientation;
//	t_tuple	v_horiz;
//	t_tuple	v_vert;
//	double	focal_length;
//	double	vh;
//	double	vw;
//	double	delta_vh;
//	double	delta_vw;
//	double	asp;
//	int		h_fov;
//	int		v_fov;
//	t_bool	flag;
//}	t_camera;

typedef struct s_camera
{
	t_4dmat	*view_matrix;
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

typedef struct s_shape
{
	t_shape_type	shape;
	t_tuple			center;
	t_tuple			color;
	t_tuple			normal;
	t_bool			inward_normal;
	double			alpha;
}	t_shape;

typedef struct s_hit
{
	t_ray		hit;
	t_tuple		p;
	t_tuple		normal;
	t_shape		shape;
	double		t;
}	t_hit;

typedef struct s_intersection
{
	float			t;
	void			*shape;
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

typedef struct	s_mater
{
	t_color	color;
	float	ambient;
	float	specular;
	float	diffuse;
	float	shine;
}	t_mater;

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
	double		alpha;
	double		radius;
}	t_sphere;

typedef struct	s_light
{
	t_color	intensity;
	t_tuple	position;
}	t_light;

typedef struct	s_inter_comp
{
	t_intersects	*intersects;
	t_shape_type	type;
	t_tuple			*normal_vec;
	t_sphere		*obj;
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
	int			object_count;
}	t_minirt;

#endif