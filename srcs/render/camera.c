/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:58:09 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/20 02:47:20 by ahaarij          ###   ########.fr       */
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
 	camera->pixel_size = (camera->half_width * 2) / camera->horizontal_canv_size;
}

t_camera	return_camera(double horiz_size, double vertic_size, double fov, t_4dmat *t)
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

t_camera	*return_camera_ptr(double horiz_size, double vertic_size, double fov)
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

t_4dmat	*view_transform(t_tuple *to, t_tuple *from, t_tuple *up)
{
	t_tuple	forward_vec;
	t_tuple	left_vec;
	t_tuple	real_up;
	t_4dmat	*orientation;
	t_4dmat	transl8;
	t_4dmat	*res;
	t_tuple	up_normalized;
	double	points[4][4];
	
	ft_bzero(&points, sizeof(double) * (4 * 4));
	forward_vec = subtract_tuples(from, to);
	up_normalized = return_tuple(up->x, up->y, up->z, VECTOR);
	normalize(&up_normalized);
	normalize(&forward_vec);
	left_vec = cross_product(&forward_vec, &up_normalized);
	normalize(&left_vec);
	real_up = cross_product(&left_vec, &forward_vec);
	points[0][0] = left_vec.x;
	points[0][1] = left_vec.y;
	points[0][2] = left_vec.z;
	points[1][0] = real_up.x;
	points[1][1] = real_up.y;
	points[1][2] = real_up.z;
	points[2][0] = -forward_vec.x;
	points[2][1] = -forward_vec.y;
	points[2][2] = -forward_vec.z;
	points[3][3] = 1;
	orientation = create_4dmat(points);
	transl8 = translation_mat(-from->x, -from->y, -from->z);
	res = mat4d_mult(orientation, &transl8);
	free(orientation);
	return (res);
}

//t_4dmat	view_transform_test(t_tuple *to, t_tuple *from, t_tuple *up)
//{
//	t_tuple	forward_vec;
//	t_tuple	left_vec;
//	t_tuple	real_up;
//	t_4dmat	orientation;
//	t_4dmat	translate_scene;
//	t_tuple	up_normalized;

//	ft_bzero(&orientation, sizeof(t_4dmat));
//	//forward_vec = add_vectors(from, to);
//	//forward_vec = subtract_tuples(from, to);
//	forward_vec = *to;
//	normalize(&forward_vec);
//	printf("Forward vector: ");
//	print_tuple_points(&forward_vec);
//	up_normalized = return_vector(0, 1, 0);
//	normalize(&up_normalized);
//	if (is_equal(forward_vec.x, 0) && is_equal(forward_vec.z, 0))
//		left_vec = return_vector(1, 0, 0);
//	else
//		left_vec = cross_product(&forward_vec, &up_normalized);
//	normalize(&left_vec);
//	real_up = cross_product(&left_vec, &forward_vec);
//	normalize(&real_up);
//	orientation.matrix[0][0] = left_vec.x;
//	orientation.matrix[0][1] = left_vec.y;
//	orientation.matrix[0][2] = left_vec.z;
//	orientation.matrix[1][0] = real_up.x;
//	orientation.matrix[1][1] = real_up.y;
//	orientation.matrix[1][2] = real_up.z;
//	orientation.matrix[2][0] = -forward_vec.x;
//	orientation.matrix[2][1] = -forward_vec.y;
//	orientation.matrix[2][2] = -forward_vec.z;
//	print_4dmatrix(&orientation);
//	printf("\n");
//	//orientation.matrix[0][3] = dot_product(from, &left_vec);
//	//orientation.matrix[1][3] = dot_product(from, &real_up);
//	//orientation.matrix[2][3] = dot_product(from, &forward_vec);
//	orientation.matrix[3][3] = 1;
//	//return (orientation);
//	translate_scene = translation_mat(-from->x, -from->y, -from->z);
//	//translate_scene = translation_mat(-dot_product(from, &left_vec), -dot_product(from, &real_up), -dot_product(from, &forward_vec));
//	(void)up;
//	return (mat4d_mult_fast_static(&orientation, &translate_scene));
//}

void debug_orthogonality(t_tuple forward_vec, t_tuple real_up, t_tuple left_vec) {
    printf("Dot(forward, up): %f\n", dot_product(&forward_vec, &real_up));
    printf("Dot(forward, left): %f\n", dot_product(&forward_vec, &left_vec));
    printf("Dot(up, left): %f\n", dot_product(&real_up, &left_vec));
}


t_4dmat	view_transform_test(t_tuple *left_vec, t_tuple *from, t_tuple *up, t_tuple *cam, t_tuple *forward_vec)
{
	// t_tuple	left_vec;
	t_tuple	real_up;
	t_4dmat	orientation;
	t_4dmat	translate_scene;
	// t_tuple	temp;

	ft_bzero(&orientation, sizeof(t_4dmat));
	// normalize(forward_vec);
	// normalize(up);
	// temp = return_vector(1, 0, 0);
	if (is_equal(forward_vec->x, 0) && is_equal(forward_vec->z, 0))
		*left_vec = return_vector(1, 0, 0);
	else
		*left_vec = cross_product(forward_vec, up);
	normalize(left_vec);
	real_up = cross_product(left_vec, forward_vec);
	normalize(&real_up);
	orientation.matrix[0][0] = left_vec->x;
	orientation.matrix[0][1] = left_vec->y;
	orientation.matrix[0][2] = left_vec->z;
	orientation.matrix[1][0] = up->x;
	orientation.matrix[1][1] = up->y;
	orientation.matrix[1][2] = up->z;
	orientation.matrix[2][0] = -forward_vec->x;
	orientation.matrix[2][1] = -forward_vec->y;
	orientation.matrix[2][2] = -forward_vec->z;
	orientation.matrix[3][3] = 1;
	(void)from;
	// debug_orthogonality(*forward_vec, real_up, *left_vec);
	translate_scene = translation_mat(-cam->x, -cam->y, -cam->z);
	(void)up;
	(void)cam;
	return (mat4d_mult_fast_static(&orientation, &translate_scene));
}


// t_4dmat	view_transform_test(t_tuple *from, t_tuple *cam, t_minirt *m)
// {
// 	normalize(&m->up);
// 	normalize(&m->left);
// 	normalize(&m->forward);
// 	// double points[4][4] = {
// 	// 	{m->left.x, m->left.y, m->left.z, 0.0f},
// 	// 	{m->up.x, m->up.y, m->up.z, 0.0f},
// 	// 	{-m->forward.x, -m->forward.y, -m->forward.z, 0.0f},
// 	// 	{0.0f, 0.0f, 0.0f, 1.0f}
// 	// };
// 	t_4dmat trans;
// 	m->cam->inverse.m11 = m->left.x;
// 	m->cam->inverse.m12 = m->left.y;
// 	m->cam->inverse.m13 = m->left.z;
// 	m->cam->inverse.m14 = 0.0f;
// 	m->cam->inverse.m21 = m->up.x;
// 	m->cam->inverse.m22 = m->up.y;
// 	m->cam->inverse.m23 = m->up.z;
// 	m->cam->inverse.m24 = 0.0f;
// 	m->cam->inverse.m31 = -m->forward.x;
// 	m->cam->inverse.m32 = -m->forward.y;
// 	m->cam->inverse.m33 = -m->forward.z;
// 	m->cam->inverse.m34 = 0.0f;
// 	m->cam->inverse.m41 = 0.0f;
// 	m->cam->inverse.m42 = 0.0f;
// 	m->cam->inverse.m43 = 0.0f;
// 	m->cam->inverse.m44 = 1.0f;
// 	(void)from;
// 	(void)cam;
// 	trans = translation_mat(-m->cam->trans.x, -m->cam->trans.y, -m->cam->trans.z);
// 	return(mat4d_mult_fast_static(&m->cam->inverse, &trans));
// }


// t_4dmat	view_transform_test(t_tuple *to, t_tuple *from, t_tuple *up)
// {
// 	t_tuple	forward_vec;
// 	t_tuple	left_vec;
// 	t_tuple	real_up;
// 	t_4dmat	orientation;
// 	t_4dmat	translate_scene;
// 	t_tuple	up_normalized;

// 	ft_bzero(&orientation, sizeof(t_4dmat));
// 	//forward_vec = subtract_tuples(from, to);
// 	forward_vec = *to;
// 	normalize(&forward_vec);
// 	up_normalized = return_vector(0, 1, 0);
// 	if (is_equal(forward_vec.x, 0) && is_equal(forward_vec.z, 0))
// 		left_vec = return_vector(1, 0, 0);
// 	else
// 		left_vec = cross_product(&forward_vec, &up_normalized);
// 	normalize(&left_vec);
// 	real_up = cross_product(&left_vec, &forward_vec);
// 	normalize(&real_up);
// 	orientation.matrix[0][0] = left_vec.x;
// 	orientation.matrix[0][1] = left_vec.y;
// 	orientation.matrix[0][2] = left_vec.z;
// 	orientation.matrix[1][0] = real_up.x;
// 	orientation.matrix[1][1] = real_up.y;
// 	orientation.matrix[1][2] = real_up.z;
// 	orientation.matrix[2][0] = -forward_vec.x;
// 	orientation.matrix[2][1] = -forward_vec.y;
// 	orientation.matrix[2][2] = -forward_vec.z;
// 	orientation.matrix[3][3] = 1;
// 	translate_scene = translation_mat(-from->x, -from->y, -from->z);
// 	(void)up;
// 	return (mat4d_mult_fast_static(&orientation, &translate_scene));
// }

