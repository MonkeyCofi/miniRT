/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:19:18 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/10 18:36:37 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define MRT_ERR \
"Malloc failed while trying to create main minirt struct\n"
# define SPH_ERR "Malloc failed while trying to create a sphere\n"
# define PL_ERR "Malloc failed while trying to create a plane\n"
# define SHP_ERR "Malloc failed while trying to create a shape\n"
# define CYL_ERR "Malloc failed while trying to create a cylinder\n"
# define CON_ERR "Malloc failed while trying to create a cone\n"
# define CAM_ERR "Malloc failed while trying to create a camera\n"
# define SHP_ERR "Malloc failed while trying to create a shape\n"
# define AMB_ERR "Malloc failed while trying to create an ambient\n"
# define LGT_ERR "Malloc failed while trying to create a light\n"
# define MLX_ERR "Malloc failed while trying to create mlx\n"
# define IMG_ERR "Malloc failed while trying to create an image\n"
# define CAM_AMT_ERR "Camera: You can only have one camera"
# define CAM_ARG_ERR "Camera: Invalid number of arguments"
# define CAM_COORD_ERR "Camera: Invalid coordinates"
# define CAM_ORIENT_ERR "Camera: Invalid orientation"
# define CAM_FOV_ERR "Camera: Invalid FOV"

#endif