/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:59:11 by pipolint          #+#    #+#             */
/*   Updated: 2024/08/23 13:08:05 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <math.h>
# include "vectors.h"
# include "camera.h"
# include "structs.h"
# include <stdio.h>
# include <fcntl.h>

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
typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}	t_ray;


int			escape(int keycode, void *param);
int			destroy(void *param);

void		set_min_max(t_vector *color);
uint32_t	get_ray_color(t_color *color);


int			fileopen(char *path, t_cameraparse *cam);
// parsing stuff, will make .h file separately for dis
int		arr_len(char	*arr[]);
double	str_to_double(char *str);
int		is_float(char *str);
void	free_arr(char *arr[]);
int	dovector(char *string, t_vector *calc);
int	parse_camera(t_cameraparse *cam, char *string);
int	parsing(char *str, t_cameraparse *cam);



#endif