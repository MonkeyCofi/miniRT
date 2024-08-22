/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:15:08 by pipolint          #+#    #+#             */
/*   Updated: 2024/08/21 19:24:29 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "minirt.h"

typedef struct	s_sphere
{
	t_color	*color;
	t_ray	*ray;
	double	radius;
	int		hit;
}	t_sphere;


#endif