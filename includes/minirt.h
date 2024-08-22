/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:59:11 by pipolint          #+#    #+#             */
/*   Updated: 2024/08/21 19:16:39 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <math.h>
# include "shapes.h"
# include "vectors.h"
# include "my_mlx.h"
# include "camera.h"
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

int			escape(int keycode, void *param);
int			destroy(void *param);

void		set_min_max(t_vector *color);
uint32_t	get_ray_color(t_color *color);

#endif