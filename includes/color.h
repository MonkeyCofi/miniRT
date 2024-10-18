/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:26:09 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/15 12:41:10 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "structs.h"

t_tuple		shade(t_minirt *minirt, t_inter_comp *intersect_comp);
t_tuple		color_at(t_minirt *minirt, t_ray *ray);
t_tuple		return_color(float red, float green, float blue, float alpha);
uint32_t	get_ray_color(t_tuple	*color);
void		set_min_max(t_tuple *color);

#endif