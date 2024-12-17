/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:59:11 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/10 21:14:49 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
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
# include "parsing.h"
# include "frees.h"

# include <string.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>

# define PI 3.1415926535897932385
# define EPSILON 0.00001f
# define MRT_ERR \
"Malloc failed while trying to create main minirt struct\n"
# define SPH_ERR "Malloc failed while trying to create a sphere\n"
# define PL_ERR "Malloc failed while trying to create a plane\n"
# define SHP_ERR "Malloc failed while trying to create a shape\n"
# define CYL_ERR "Malloc failed while trying to create a cylinder\n"
# define CON_ERR "Malloc failed while trying to create a cone\n"
# define CAM_ERR "Malloc failed while trying to create a camera\n"
# define SHP_ERR "Malloc failed while trying to create a shape\n"
# define AMB_ERR "Malloc failed while trying to create an ambient\n"
# define LGT_ERR "Malloc failed while trying to create a light\n"
# define MLX_ERR "Malloc failed while trying to create mlx\n"
# define IMG_ERR "Malloc failed while trying to create an image\n"
# define CAM_AMT_ERR "Camera: You can only have one camera"
# define CAM_ARG_ERR "Camera: Invalid number of arguments"
# define CAM_COORD_ERR "Camera: Invalid coordinates"
# define CAM_ORIENT_ERR "Camera: Invalid orientation"
# define ERR_SPH_PARAM "Invalid sphere parameters\n"
# define ERR_CYL_PARAM "Invalid cylinder parameters\n"
# define ERR_DIF_EX "Error\nDiffuse: Diffuse already exists\n"
# define ERR_DIF_INV "Error\nDiffuse: Invalid keyword\n"
# define ERR_DIF_VAL "Error\nDiffuse: Invalid value\n"
# define ERR_SHP_AMB_EX "Error\nShape ambient: ambient already exists\n"
# define ERR_SHP_AMB_INV "Error\nShape ambient: Invalid keyword\n"
# define ERR_SHP_AMB_VAL "Error\nShape ambient: Invalid value\n"
# define ERR_PAT_EX "Error\nPattern: Pattern already exists\n"
# define ERR_PAT_INV "Error\nPattern: Invalid keyword\n"
# define ERR_PAT_VAL "Error\nPattern: Invalid color\n"
# define ERR_PAT_PAR "Error\nInvalid paramters for pattern\n"

# ifdef __APPLE__
#  define APP 1
#  include "../mlx/mlx.h"
#  define APPLE 1
#  define HEIGHT 400
#  define WIDTH 400
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
#  include "../minilibx-linux/mlx.h"
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

int			escape(int keycode, void *param);

int			destroy(void *param);

// utils stuff
int			arr_len(char	*arr[]);

double		str_to_double(char *str);

int			is_double(char *str);

int			free_arr(char *arr[]);

t_tuple		lighting(t_inter_comp *intersection, t_light *light, \
												t_bool in_shadow, t_minirt *m);

//int			get_key_pressed(int keycode, t_mlx *mlx, int scale);
void		draw_pixel(t_mlx *mlx, int x, int y, int color);

t_mater		*create_default_material(t_minirt *m);

int			closert(t_minirt *m);

int			event_loop(t_minirt *m);

t_tuple		checkerboard_cylinder(t_pattern pattern, \
									t_inter_comp *intersection);

t_tuple		checkerboard_cap(t_pattern pattern, t_tuple point);

int			delta_time(void *param);

int			get_key_pressed(int keycode, t_minirt *m);

int			get_key_released(int keycode, t_minirt *m);

void		camera_movement(t_minirt *m);

void		change_cammove(t_minirt *m);

int			parse_bon_sp(t_minirt *m, t_shape *shape, \
			char **tokens, t_bool is_sphere);

int			resetcam(t_minirt *m);

int			check_magnitude(t_minirt *m, t_tuple *vector, char *line);

void		write_check(t_minirt *m, char *str);

int			write_and_return(t_minirt *m, char *str, int return_num);

#endif