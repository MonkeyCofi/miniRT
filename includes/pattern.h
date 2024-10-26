/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:58:08 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/26 18:02:55 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATTERN_H
# define PATTERN_H

# include "structs.h"

t_pattern	create_pattern(t_tuple color_one, t_tuple color_two, int scale);
t_tuple		pattern_at_point(t_pattern pattern, t_tuple point);
t_tuple		checkerboard(t_pattern pattern, t_tuple point);
t_tuple		checkerboard_sphere(t_pattern pattern, t_inter_comp *intersection);

#endif