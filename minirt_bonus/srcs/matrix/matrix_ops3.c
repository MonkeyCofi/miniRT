/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:34:49 by ahaarij           #+#    #+#             */
/*   Updated: 2024/11/25 16:36:36 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_3dmat	*submat_4d(t_4dmat *matrix, int row, int column)
{
	double	resultant[3][3];
	int		i;
	int		j;
	int		k;
	int		l;

	i = -1;
	k = 0;
	while (++i < 4)
	{
		if (i == row)
			continue ;
		j = -1;
		l = 0;
		while (++j < 4)
		{
			if (j == column)
				continue ;
			resultant[k][l++] = matrix->matrix[i][j];
		}
		k++;
	}
	return (create_3dmat(resultant));
}

double	minor_3d(t_3dmat *mat, int row, int column)
{
	t_2dmat	*submatrix;
	double	ret;

	submatrix = submat_3d(mat, row, column);
	ret = determinant(submatrix, NULL, NULL);
	free(submatrix);
	return (ret);
}

double	minor_4d(t_4dmat *mat, int row, int column)
{
	t_3dmat	*submatrix;
	double	ret;

	submatrix = submat_4d(mat, row, column);
	ret = determinant(NULL, submatrix, NULL);
	free(submatrix);
	return (ret);
}

double	cofactor_3d(t_3dmat *mat, int row, int column)
{
	double	minor;
	double	cofact[3][3];

	minor = minor_3d(mat, row, column);
	cofact[0][0] = 1;
	cofact[0][1] = -1;
	cofact[0][2] = 1;
	cofact[1][0] = -1;
	cofact[1][1] = 1;
	cofact[1][2] = -1;
	cofact[2][0] = 1;
	cofact[2][1] = -1;
	cofact[2][2] = 1;
	return (minor * cofact[row][column]);
}

double	cofactor_4d(t_4dmat *mat, int row, int column)
{
	double	minor;
	double	cofact[4][4];

	minor = minor_4d(mat, row, column);
	cofact[0][0] = 1;
	cofact[0][1] = -1;
	cofact[0][2] = 1;
	cofact[0][3] = -1;
	cofact[1][0] = -1;
	cofact[1][1] = 1;
	cofact[1][2] = -1;
	cofact[1][3] = 1;
	cofact[2][0] = 1;
	cofact[2][1] = -1;
	cofact[2][2] = 1;
	cofact[2][3] = -1;
	cofact[3][0] = -1;
	cofact[3][1] = 1;
	cofact[3][2] = -1;
	cofact[3][3] = 1;
	return (minor * cofact[row][column]);
}
