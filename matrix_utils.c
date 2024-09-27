/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:54:54 by pipolint          #+#    #+#             */
/*   Updated: 2024/09/27 16:57:58 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	*create_matrix(int size)
{
	t_matrix	*newMatrix;
	
	newMatrix = malloc(sizeof(t_matrix));
	if (!newMatrix)
		return (NULL);
	newMatrix->matrix = malloc(sizeof(float *) * size);
	newMatrix->size = size;
	return (newMatrix);
}

void	set_matrix(t_matrix *m, float **points)
{
	int	i;
	int	j;
	int	size;

	size = m->size;
	i = -1;
	j = -1;
	while (++i < size)
	{
		m->matrix[i] = malloc(sizeof(float) * size);
		while (++j < size)
			m->matrix[i][j] = points[i][j];
	}
}

void	set_column(int size, int current_row, float **matrix, float values[])
{
	int	i;

	i = -1;
	while (++i < size)
		matrix[current_row][i] = values[i];
}

void	print_matrix(t_matrix *m)
{
	int size;
	int	i;
	int	j;
	
	size = m->size;
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			printf("%.5f ", m->matrix[i][j]);
		}
		printf("\n");
	}
}