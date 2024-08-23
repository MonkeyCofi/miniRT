/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:58:09 by pipolint          #+#    #+#             */
/*   Updated: 2024/08/23 15:17:16 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_cam(t_minirt *minirt)
{
	minirt->cam->asp = ((double)WIDTH / HEIGHT);
	minirt->cam->vh = HEIGHT * 2;
	minirt->cam->vw = WIDTH * 2;
	minirt->cam->focal_length = 1.0;	// the distance from te camera to the viewport
	// set_vector_points(&minirt->cam->camera, 0, 0, 0);
	set_vector_points(&minirt->cam->v_horiz, minirt->cam->vh, 0, 0);
	set_vector_points(&minirt->cam->v_vert, 0, -minirt->cam->vw, 0);
	minirt->cam->delta_vh = minirt->cam->vh / HEIGHT;
	minirt->cam->delta_vw = minirt->cam->vw / WIDTH;
	// cam.fov = 45 * (PI / 180);
}
