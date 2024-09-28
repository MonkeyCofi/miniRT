/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:54:54 by pipolint          #+#    #+#             */
/*   Updated: 2024/09/28 21:02:18 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_2dmat	*create_2dmat(float points[2][2])
{
	t_2dmat	*new_mat;
	int		i;
	int		j;

	new_mat = ft_calloc(1, sizeof(t_2dmat));
	if (!new_mat)
		return (NULL);
	i = -1;
	while (++i < 2)
	{
		j = -1;
		while (++j < 2)
			new_mat->matrix[i][j] = points[i][j];
	}
	return (new_mat);
}

t_3dmat	*create_3dmat(float points[3][3])
{
	t_3dmat	*new_mat;
	int		i;
	int		j;
	
	new_mat = ft_calloc(1, sizeof(t_3dmat));
	if (!new_mat)
		return (NULL);
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			new_mat->matrix[i][j] = points[i][j];
	}
	return (new_mat);
}

t_4dmat	*create_4dmat(float points[4][4])
{
	t_4dmat	*new_mat;
	int		i;
	int		j;
	
	new_mat = ft_calloc(1, sizeof(t_4dmat));
	if (!new_mat)
		return (NULL);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			new_mat->matrix[i][j] = points[i][j];
	}
	return (new_mat);
}

void	print_2dmatrix(t_2dmat *m)
{
	printf("% .5f ", m->m11);
	printf("% .5f\n", m->m12);
	printf("% .5f ", m->m21);
	printf("% .5f\n", m->m22);
}

void	print_3dmatrix(t_3dmat *m)
{
	printf("% .5f ", m->m11);
	printf("% .5f ", m->m12);
	printf("% .5f\n", m->m13);
	printf("% .5f ", m->m21);
	printf("% .5f ", m->m22);
	printf("% .5f\n", m->m23);
	printf("% .5f ", m->m31);
	printf("% .5f ", m->m32);
	printf("% .5f\n", m->m33);
}
void	print_4dmatrix(t_4dmat *m)
{
	printf("% .5f ", m->m11);
	printf("% .5f ", m->m12);
	printf("% .5f ", m->m13);
	printf("% .5f\n", m->m14);
	printf("% .5f ", m->m21);
	printf("% .5f ", m->m22);
	printf("% .5f ", m->m23);
	printf("% .5f\n", m->m24);
	printf("% .5f ", m->m31);
	printf("% .5f ", m->m32);
	printf("% .5f ", m->m33);
	printf("% .5f\n", m->m34);
	printf("% .5f ", m->m41);
	printf("% .5f ", m->m42);
	printf("% .5f ", m->m43);
	printf("% .5f\n", m->m44);
}
