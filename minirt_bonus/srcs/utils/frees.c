/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:03:24 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/10 15:13:44 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_lights(t_minirt *m)
{
	int	i;

	i = -1;
	while (++i < m->light_count)
	{
		free(m->lights[i]);
	}
	free(m->lights);
}

void	free_minirt(t_minirt *m, int exit_code)
{
	if (m)
	{
		if (m->ambient)
			free(m->ambient);
		if (m->shapes)
			free_shapes(m);
		if (m->lights)
			free_lights(m);
		if (m->mlx)
			free(m->mlx);
		if (m->cam)
			free(m->cam);
		if (m->file_fd != -1)
			close(m->file_fd);
		free(m);
		exit(exit_code);
	}
	exit(exit_code);
}

void	*calloc_and_check(size_t memb_size, size_t nmemb, t_minirt *m,
						char *err_msg)
{
	void	*ptr;

	ptr = ft_calloc(nmemb, memb_size);
	if (ptr == NULL)
	{
		if (write(2, err_msg, ft_strlen(err_msg)) == -1)
			free_minirt(m, EXIT_FAILURE);
		free_minirt(m, EXIT_FAILURE);
	}
	return (ptr);
}

void	free_shapes(t_minirt *minirt)
{
	int	i;

	i = -1;
	while (++i < minirt->object_count)
	{
		if (minirt->shapes[i]->shape)
			free(minirt->shapes[i]->shape);
		if (minirt->shapes[i]->material)
		{
			if (minirt->shapes[i]->material->texture)
				free(minirt->shapes[i]->material->texture);
			free(minirt->shapes[i]->material);
		}
		free(minirt->shapes[i]);
	}
	free(minirt->shapes);
}
