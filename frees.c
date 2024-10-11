/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:03:24 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/11 20:04:19 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_shapes(t_minirt *minirt)
{
	int	i;

	i = -1;
	while (++i < minirt->object_count)
		free(minirt->spheres[i]);
	free(minirt->spheres);
}
