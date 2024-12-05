/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:03:24 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/05 20:22:36 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_light(t_minirt *m)
{
	if (m->light)
		free(m->light);
}

void	free_minirt(t_minirt *m, int exit_code)
{
	if (m)
	{
		if (m->ambient)
			free(m->ambient);
		if (m->shapes)
			free_shapes(m);
		free_light(m);
		if (m->mlx)
			free(m->mlx);
		if (m->cam)
			free(m->cam);
		free(m);
		exit(exit_code);
		//exit(EXIT_FAILURE);
	}
	exit(exit_code);
	//exit(EXIT_FAILURE);
}

void	*calloc_and_check(size_t memb_size, size_t nmemb, t_minirt *m,
						char *err_msg)
{
	void	*ptr;

	ptr = ft_calloc(nmemb, memb_size);
	if (ptr == NULL)
	{
		if (write(2, err_msg, ft_strlen(err_msg)) == -1)
			free_minirt(m, 1);
		free_minirt(m, 1);
	}
	return (ptr);
}

void	free_shapes(t_minirt *minirt)
{
	int	i;

	i = -1;
	while (++i < minirt->object_count)
	{
		free(minirt->shapes[i]->shape);
		free(minirt->shapes[i]);
	}
	free(minirt->shapes);
}
// put this up
// i = -1;
// while (++i < minirt->light_count)
// 	free(minirt->lights[i]);
// free(minirt->lights);
