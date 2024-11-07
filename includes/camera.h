/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:15:14 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/07 09:18:37 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "structs.h"

t_camera	return_camera(double horiz_size, double vertic_size, double fov, t_4dmat *t);
t_camera	*return_camera_ptr(double horiz_size, double vertic_size, double fov);
t_4dmat		*view_transform(t_tuple *to, t_tuple *from, t_tuple *up);
t_4dmat		view_transform_test(t_tuple *to, t_tuple *from, t_tuple *up, t_tuple *cam);

#endif