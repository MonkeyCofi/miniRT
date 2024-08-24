/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:19:36 by pipolint          #+#    #+#             */
/*   Updated: 2024/08/25 02:25:57 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

void	set_min_max(t_vector *color)
{
	if (color->x < 0)
		color->x = 0;
	else if (color->x > 1)
		color->x = 1;
	if (color->y < 0)
		color->y = 0;
	else if (color->y > 1)
		color->y = 1;
	if (color->z < 0)
		color->z = 0;
	else if (color->z > 1)
		color->z = 1;
}

uint32_t	get_ray_color(t_color	*color)
{
	uint32_t		res;
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	uint8_t			a;

	set_min_max(&color->colors);
	r = color->colors.x * 255;
	g = color->colors.y * 255;
	b = color->colors.z * 255;
	a = color->alpha;
	res = a << 24 | r << 16 | g << 8 | b;
	return (res);
}

uint32_t	get_ray_coloraarij(t_vector	*color)
{
	uint32_t		res;
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	uint8_t			a;

	set_min_max(color);
	r = color->x * 255;
	g = color->y * 255;
	b = color->z * 255;
	a = 1;
	res = a << 24 | r << 16 | g << 8 | b;
	return (res);
}
