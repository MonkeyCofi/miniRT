/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:59:11 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/29 17:36:54 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft_notclone/libft.h"
# include "../mlx/mlx.h"
# include "vectors.h"
# include "matrix.h"
# include "camera.h"
# include "structs.h"
# include "transformations.h"
# include "sphere.h"
# include "intersects.h"
# include "color.h"
# include "material.h"
# include "init.h"
# include "shapes.h"
# include "render.h"
# include "threads.h"
# include "pattern.h"
# include "ppm.h"

# include <math.h>
# include <stdio.h>
# include <fcntl.h>

# define PI 3.1415926535897932385
# define EPSILON 0.00001f
# define DEG_RAD(x) x * (PI / 180) 
//# define MAX_INTERSECTS 200

# ifdef __APPLE__
#  define APP 1
//#  define HEIGHT 1080
//#  define WIDTH 1920
#  define APPLE 1
#  define HEIGHT 800
#  define WIDTH 1000
#  define W 13
#  define A 0
#  define S 1
#  define D 2
#  define Q 12
#  define E 14
#  define R 15
#  define B 11
#  define P 35
#  define G 5
#  define Y 16
#  define UP 126
#  define LEFT 123
#  define DOWN 125
#  define RIGHT 124
#  define PLUS 24
#  define MINUS 27
#  define ESC 53
# else
#  define APPLE 0
#  define HEIGHT 720
#  define WIDTH 1080
#  define W 119
#  define A 97
#  define S 115
#  define D 100
#  define Q 113
#  define E 101
#  define R 114
#  define G 0
#  define P 0
#  define B 0
#  define Y 0
#  define UP 65362
#  define LEFT 65361
#  define DOWN 65364
#  define RIGHT 65363
#  define PLUS 61
#  define MINUS 45
#  define APP 0
#  define ESC 65307
# endif

//# ifdef __APPLE__
//#  define HEIGHT 1080
//#  define WIDTH 1920
//#  define APPLE 1
//#  define ESC 53
//#  else
//#  define HEIGHT 800
//#  define WIDTH 1000
//#  define APPLE 0
//#  define ESC 65307
//# endif

typedef struct s_cameraparse
{
	t_tuple		campos;
	int			fov;
	int			flag;
	t_tuple	vec;
}	t_cameraparse;

int			escape(int keycode, void *param);
int			destroy(void *param);

// parsing stuff, will make .h file separately for dis
int			fileopen(char *path, t_minirt *minirt);
int			arr_len(char	*arr[]);
double		str_to_double(char *str);
int			is_double(char *str);
void		free_arr(char *arr[]);
int			dovector(char *string, t_tuple *calc);
int			parse_camera(t_minirt *minirt, char *string);
int			parsing(char *str, t_minirt *minirt, int *i, int *j);

//t_tuple		lighting(t_mater *material, t_light *light, t_tuple point, t_tuple eye_vector, t_tuple normal_vector);
t_tuple		lighting(t_inter_comp *intersection, t_light *light, t_tuple point, t_tuple eye_vector, t_tuple normal_vector, t_bool in_shadow);
//t_tuple		lighting(t_shape *shape, t_light *light, t_tuple point, t_tuple eye_vector, t_tuple normal_vector, t_bool in_shadow);
t_light		create_light(t_tuple intensity, t_tuple position);
t_tuple		get_reflected_ray(t_tuple *from, t_tuple *normal);

//int			get_key_pressed(int keycode, t_mlx *mlx, int scale);
void		draw_pixel(t_mlx *mlx, int x, int y, int color);
t_mater		*create_default_material();

int			closert(t_minirt *m);
void		adjust_yaw(t_minirt *m, int i);
void		adjust_pitch(t_minirt *m, int i);
int			get_key_pressed(int keycode, t_hook_params *hooks);
t_tuple checkerboard_cylinder(t_pattern pattern, t_inter_comp *intersection);
t_tuple checkerboard_cap(t_pattern pattern, t_tuple point);

#endif