/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:19:18 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/09 16:52:59 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define MRT_ERR \
"Error\nMalloc failed while trying to create main minirt struct\n"
# define SPH_ERR "Error\nMalloc failed while trying to create a sphere\n"
# define PL_ERR "Error\nMalloc failed while trying to create a plane\n"
# define SHP_ERR "Error\nMalloc failed while trying to create a shape\n"
# define CYL_ERR "Error\nMalloc failed while trying to create a cylinder\n"
# define CON_ERR "Error\nMalloc failed while trying to create a cone\n"
# define CAM_ERR "Error\nMalloc failed while trying to create a camera\n"
# define SHP_ERR "Error\nMalloc failed while trying to create a shape\n"
# define AMB_ERR "Error\nMalloc failed while trying to create an ambient\n"
# define LGT_ERR "Error\nMalloc failed while trying to create a light\n"
# define MLX_ERR "Error\nMalloc failed while trying to create mlx\n"
# define IMG_ERR "Error\nMalloc failed while trying to create an image\n"
# define CAM_AMT_ERR "Error\nCamera: You can only have one camera"
# define CAM_ARG_ERR "Error\nCamera: Invalid number of arguments"
# define CAM_COORD_ERR "Error\nCamera: Invalid coordinates"
# define CAM_ORIENT_ERR "Error\nCamera: Invalid orientation"
# define CAM_FOV_ERR "Error\nCamera: Invalid FOV"

#endif