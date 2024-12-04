/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:58:08 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/04 19:36:30 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATTERN_H
# define PATTERN_H

# include "structs.h"

t_pattern	*create_pattern(t_tuple color_one, t_tuple color_two, \
											int scale, t_pattern *pattern);

t_tuple		checkerboard(t_pattern pattern, t_tuple point, \
											t_tuple plane_normal);

t_tuple		checkerboard_sphere(t_pattern pattern, t_inter_comp *intersection);

t_tuple		texture_sphere(t_inter_comp *intersection, \
							double *phi, double *theta);

t_tuple		normal_from_sample(t_inter_comp *intersection);

#endif