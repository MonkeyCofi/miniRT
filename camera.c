/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:58:09 by pipolint          #+#    #+#             */
/*   Updated: 2024/08/18 13:10:20 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


t_camera	init_cam(void)
{
	t_camera	cam;

	ft_bzero(&cam, sizeof(t_camera));
	cam.asp = ((double)WIDTH / HEIGHT);
	cam.vh = HEIGHT * 2;
	cam.vw = WIDTH * 2;
	cam.focal_length = 1.0;	// the distance from te camera to the viewport
	set_vector_points(&cam.camera, 0, 0, 2);
	set_vector_points(&cam.v_horiz, cam.vh, 0, 0);
	set_vector_points(&cam.v_vert, 0, -cam.vw, 0);
	cam.delta_vh = cam.vh / HEIGHT;
	cam.delta_vw = cam.vw / WIDTH;
	cam.fov = 45 * (PI / 180);
	return (cam);
}
