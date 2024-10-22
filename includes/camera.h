/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:15:14 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/22 21:45:17 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "structs.h"

t_camera	return_camera(double horiz_size, double vertic_size, double fov, t_4dmat *t);
t_camera	*return_camera_ptr(double horiz_size, double vertic_size, double fov, t_4dmat *t);
t_4dmat		*view_transform(t_tuple *to, t_tuple *from, t_tuple *up);

#endif