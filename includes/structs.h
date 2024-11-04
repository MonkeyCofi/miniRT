/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:09:45 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/04 13:06:02 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdlib.h>
# include "../libft_notclone/libft.h"

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
	none,
	scale,
	rotate_x,
	rotate_y,
	rotate_z,
	translate,
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
		double	x;
		double	y;
		double	z;
		double	w;
	};
	struct
	{
		double	r;
		double	g;
		double	b;
		double	a;
	};
}	t_tuple;

typedef union u_2dmat
{
	struct
	{
		double	m11;
		double	m12;
		double	m21;
		double	m22;
	};
	double	matrix[2][2];
}	t_2dmat;

typedef union u_3dmat
{
	struct
	{
		double	m11;
		double	m12;
		double	m13;
		double	m21;
		double	m22;
		double	m23;
		double	m31;
		double	m32;
		double	m33;
	};
	double	matrix[3][3];
}	t_3dmat;

typedef union u_4dmat
{
	struct
	{
		double	m11;
		double	m12;
		double	m13;
		double	m14;
		double	m21;
		double	m22;
		double	m23;
		double	m24;
		double	m31;
		double	m32;
		double	m33;
		double	m34;
		double	m41;
		double	m42;
		double	m43;
		double	m44;
	};
	double	matrix[4][4];
}	t_4dmat;

typedef struct s_camera
{
	//t_4dmat	*view_matrix;
	t_4dmat	view_matrix;
	//t_4dmat	*inverse;
	t_4dmat	inverse;
	double	horizontal_canv_size;
	double	vertical_canv_size;
	double	pixel_size;
	double	fov;
	double	aspect;
	double	half_view;
	double	half_width;
	double	half_height;
	int		flag;
}	t_camera;

typedef struct s_ray
{
	t_tuple	origin;
	t_tuple	direction;
}	t_ray;

typedef struct	s_pattern
{
	t_tuple	color_one;
	t_tuple	color_two;
	int		pattern_scale;
}	t_pattern;

typedef struct	s_mater
{
	t_tuple		color;
	t_pattern	pattern;
	double		ambient;
	double		specular;
	double		diffuse;
	double		shine;
	t_bool		is_patterned;
}	t_mater;


typedef struct s_shape
{
	t_shape_type	type;
	t_pattern		pattern;
	t_tuple			coords;
	t_tuple			orientation;
	t_4dmat			transform;
	t_4dmat			*inverse_mat;
	t_4dmat			translation_mat;
	t_4dmat			rotation_mat;
	t_4dmat			scaling_mat;
	t_4dmat			*inverse_transpose;
	t_mater			*material;
	t_bool			patterned;
	t_tuple			(*normal)(struct s_shape *, t_tuple);
	t_bool			(*intersect)(t_minirt *, t_intersects *, t_ray *, int);
	double			r;
	double			h;
	void			*shape;
}	t_shape;

typedef struct s_intersection
{
	double			t;
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
	double		t;
}	t_hit;

typedef struct s_sphere
{
	t_tuple		color;
	t_tuple		normal;
	t_tuple		center;
	t_mater		*material;
	double		alpha;
	double		radius;
	double		diameter;
}	t_sphere;

typedef struct	s_plane
{
	t_tuple	point;
	t_tuple	normal;
	t_mater	*material;
}	t_plane;

typedef struct	s_light
{
	t_tuple	intensity;
	t_tuple	position;
	double	brightness;
}	t_light;

typedef struct	s_cylinder
{
	t_tuple			orientation;
	t_tuple			point;
	t_tuple			normal;
	t_mater			*material;
	t_bool			is_closed;
	double			minimum;
	double			maximum;
	double			radius;
	t_shape_type	type;
}	t_cylinder;

typedef struct	s_cone
{
	double			radius;
	double			minimum;
	double			maximum;
	t_bool			is_closed;
	t_tuple			point;
	t_mater			*material;
	t_shape_type	type;
}	t_cone;

typedef struct	s_pixel
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_pixel;

typedef struct	s_ppm
{
	enum	s_ppm_type
	{
		P3,
		P6,
	}	t_ppm_type;
	char	*filename;
	t_pixel	*buffer;
	t_tuple	**colors;
	int		height;
	int		width;
	int		intensity;
}	t_ppm;

typedef struct	s_inter_comp
{
	t_intersects	*intersects;
	t_shape_type	type;
	t_tuple			normal_vec;
	t_shape			*obj;
	t_mater			*material;
	t_tuple			point;
	t_tuple			point_adjusted;
	t_tuple			eye_vec;
	t_ppm			*ppm;
	t_bool			is_inside_object;
	double			t;
}	t_inter_comp;

typedef struct s_ambient
{
	double			ratio;
	t_tuple			color;
	int				flag;
}	t_ambient;

typedef struct s_minirt
{
	t_ambient	*ambient;
	t_mlx		*mlx;
	t_camera	*cam;
	t_shape		**shapes;
	t_light		**lights;
	t_tuple		from;
	t_tuple		to;
	t_tuple		up;
	t_ppm		*ppm;
	double		pitch;
	double		yaw;
	int			object_count;
	int			light_count;
}	t_minirt;

typedef struct s_hook_params
{
	t_mlx 		*mlx;
	t_minirt 	*m;
	t_tuple		original_from;
	t_tuple		original_to;
	t_tuple		original_up;
}	t_hook_params;

typedef struct	s_transform
{
	t_trans	transformations[5];
	t_tuple	scaling;
	t_tuple	translation;
	double	rotation_x;
	double	rotation_y;
	double	rotation_z;
}	t_transform;

#endif