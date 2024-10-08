/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:58:09 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/08 13:43:56 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//void	init_cam(t_minirt *minirt)
//{
//	minirt->cam->h_fov = 60;
//	minirt->cam->asp = ((double)WIDTH / HEIGHT);
//	minirt->cam->vh = HEIGHT * 2;
//	minirt->cam->vw = WIDTH * 2;
//	minirt->cam->focal_length = 1.0;	// the distance from te camera to the viewport
//	//set_tuple_points(&minirt->cam->camera, 0, 0, 0);
//	set_vector_points(&minirt->cam->v_horiz, minirt->cam->vh, 0, 0);
//	scalar(&minirt->cam->v_horiz, minirt->cam->h_fov);
//	set_vector_points(&minirt->cam->v_vert, 0, -minirt->cam->vw, 0);
//	minirt->cam->delta_vh = minirt->cam->vh / HEIGHT;
//	minirt->cam->delta_vw = minirt->cam->vw / WIDTH;
//	minirt->cam->flag = false;
//	// cam.fov = 45 * (PI / 180);
//}

void	get_pixel_size(t_camera *camera)
{
	float	aspect;

	aspect = camera->horizontal_canv_size / camera->vertical_canv_size;
	camera->half_view = tan(camera->fov / 2);
	if (aspect < 1)
	{
		camera->half_height = camera->half_view;
		camera->half_width = camera->half_view * aspect;
	}
	else
	{
		camera->half_width = camera->half_view;
		camera->half_height = camera->half_view / aspect;
	}
 	camera->pixel_size = (camera->half_width * 2) / camera->horizontal_canv_size;
}

t_camera	return_camera(float horiz_size, float vertic_size, float fov, t_4dmat *t)
{
	t_camera	cam;
	float		iden[4][4];

	ft_bzero(iden, (4 * 4) * sizeof(float));
	cam.horizontal_canv_size = horiz_size;
	cam.vertical_canv_size = vertic_size;
	cam.fov = fov;
	if (t)
		cam.view_matrix = t;
	else
	{
		iden[0][0] = 1;
		iden[1][1] = 1;
		iden[2][2] = 1;
		iden[3][3] = 1;
		cam.view_matrix = create_4dmat(iden);
	}
	get_pixel_size(&cam);
	return (cam);
}
