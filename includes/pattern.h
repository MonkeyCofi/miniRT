/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:58:08 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/28 10:22:44 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATTERN_H
# define PATTERN_H

# include "structs.h"

t_pattern	*create_pattern(t_tuple color_one, t_tuple color_two, \
											int scale, t_pattern *pattern);

t_tuple		pattern_at_point(t_pattern pattern, t_tuple point);

t_tuple		checkerboard(t_pattern pattern, t_tuple point, \
											t_tuple plane_normal);

t_tuple		checkerboard_sphere(t_pattern pattern, t_inter_comp *intersection);

double		*sphere_uv(t_tuple point);

t_tuple		texture_sphere(t_inter_comp *intersection, t_ppm *tex);

t_tuple		texture_plane(t_inter_comp *intersection, t_ppm *tex);

#endif