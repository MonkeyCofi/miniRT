/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:48:13 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/02 18:04:12 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "structs.h"

t_2dmat	*create_2dmat(float points[2][2]);
t_3dmat	*create_3dmat(float points[3][3]);
t_4dmat	*create_4dmat(float points[4][4]);
void	print_2dmatrix(t_2dmat *m);
void	print_3dmatrix(t_3dmat *m);
void	print_4dmatrix(t_4dmat *m);

t_2dmat	*submat_3d(t_3dmat *matrix, int row, int column);
t_3dmat	*submat_4d(t_4dmat *matrix, int row, int column);
t_4dmat	identity();
t_4dmat	*transpose(t_4dmat *matrix);

float	determinant(t_2dmat *mat_2d, t_3dmat *mat_3d, t_4dmat *mat_4d);
float	minor_3d(t_3dmat *mat, int row, int column);
float	cofactor_3d(t_3dmat *mat, int row, int column);
float	minor_4d(t_4dmat *mat, int row, int column);
float	cofactor_4d(t_4dmat *mat, int row, int column);

t_4dmat	*create_4dcofactor(t_4dmat *mat);
t_bool	inverse_mat(t_4dmat *mat, t_4dmat **ptr);

t_bool	mat2d_cmp(t_2dmat *mat_one, t_2dmat *mat_two);
t_bool	mat3d_cmp(t_3dmat *mat_one, t_3dmat *mat_two);
t_bool	mat4d_cmp(t_4dmat *mat_one, t_4dmat *mat_two);

t_2dmat	*mat2d_mult(t_2dmat *mat_one, t_2dmat *mat_two);
t_3dmat	*mat3d_mult(t_3dmat *mat_one, t_3dmat *mat_two);
t_4dmat	*mat4d_mult(t_4dmat *mat_one, t_4dmat *mat_two);
t_tuple	*tuple_mult(t_4dmat *mat, t_tuple *tuple);

void	copy_mat(t_4dmat *mat_one, t_4dmat *mat_two);

#endif