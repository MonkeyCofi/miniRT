/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:58:09 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/10 18:55:36 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_pixel_size(t_camera *camera)
{
	double	aspect;

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
	camera->pixel_size = (camera->half_width * 2) / \
	camera->horizontal_canv_size;
}

t_camera	return_camera(double horiz_size, double vertic_size, double fov, \
t_4dmat *t)
{
	t_camera	cam;

	cam.horizontal_canv_size = horiz_size;
	cam.vertical_canv_size = vertic_size;
	cam.fov = fov;
	cam.view_matrix = identity();
	(void)t;
	get_pixel_size(&cam);
	return (cam);
}

t_camera	*return_camera_ptr(double horiz_size, double vertic_size, \
double fov)
{
	t_camera	*cam;

	cam = ft_calloc(1, sizeof(t_camera));
	cam->horizontal_canv_size = horiz_size;
	cam->vertical_canv_size = vertic_size;
	cam->fov = fov;
	cam->view_matrix = identity();
	get_pixel_size(cam);
	return (cam);
}

t_4dmat	view_transform(t_tuple *left_vec, t_tuple *up, \
t_tuple *cam, t_tuple *forward)
{
	t_tuple	real_up;
	t_4dmat	orientation;
	t_4dmat	translate_scene;

	ft_bzero(&orientation, sizeof(t_4dmat));
	if (is_equal(forward->x, 0) && is_equal(forward->z, 0))
		*left_vec = return_vector(1, 0, 0);
	else
		*left_vec = cross_product(forward, up);
	normalize(left_vec);
	real_up = cross_product(left_vec, forward);
	normalize(&real_up);
	orientation.matrix[0][0] = left_vec->x;
	orientation.matrix[0][1] = left_vec->y;
	orientation.matrix[0][2] = left_vec->z;
	orientation.matrix[1][0] = up->x;
	orientation.matrix[1][1] = up->y;
	orientation.matrix[1][2] = up->z;
	orientation.matrix[2][0] = -forward->x;
	orientation.matrix[2][1] = -forward->y;
	orientation.matrix[2][2] = -forward->z;
	orientation.matrix[3][3] = 1;
	translate_scene = translation_mat(-cam->x, -cam->y, -cam->z);
	return (mat4d_mult(&orientation, &translate_scene));
}
