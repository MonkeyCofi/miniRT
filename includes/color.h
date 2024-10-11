/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:26:09 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/11 21:30:22 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "structs.h"

t_tuple		shade(t_minirt *minirt, t_inter_comp *intersect_comp);
t_tuple		color_at(t_minirt *minirt, t_ray *ray);
t_color		return_color(float red, float green, float blue, float alpha);
uint32_t	get_ray_color(t_color	*color);
void		set_min_max(t_tuple *color);

#endif