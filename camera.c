/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:58:09 by pipolint          #+#    #+#             */
/*   Updated: 2024/08/24 20:21:13 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_cam(t_minirt *minirt)
{
	minirt->cam->asp = ((double)WIDTH / HEIGHT);
	minirt->cam->vh = HEIGHT * 2;
	minirt->cam->vw = WIDTH * 2;
	minirt->cam->focal_length = 1.0;	// the distance from te camera to the viewport
	//set_vector_points(&minirt->cam->camera, 0, 0, 0);
	set_vector_points(&minirt->cam->v_horiz, minirt->cam->vh, 0, 0);
	set_vector_points(&minirt->cam->v_vert, 0, -minirt->cam->vw, 0);
	minirt->cam->delta_vh = minirt->cam->vh / HEIGHT;
	minirt->cam->delta_vw = minirt->cam->vw / WIDTH;
	minirt->cam->flag = false;
	// cam.fov = 45 * (PI / 180);
}
