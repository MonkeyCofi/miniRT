/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:15:14 by pipolint          #+#    #+#             */
/*   Updated: 2024/08/21 16:16:56 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "vectors.h"

typedef struct s_camera
{
	t_vector	camera;
	t_vector	v_horiz;
	t_vector	v_vert;
	double		focal_length;
	double		vh;
	double		vw;
	double		delta_vh;
	double		delta_vw;
	double		asp;
	double		fov;
}	t_camera;

t_camera	init_cam(void);

#endif