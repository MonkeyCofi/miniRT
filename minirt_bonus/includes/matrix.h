/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:48:13 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/10 19:02:39 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "structs.h"

t_2dmat	*create_2dmat(double points[2][2]);
t_3dmat	*create_3dmat(double points[3][3]);
t_4dmat	*create_4dmat(double points[4][4]);

void	print_3dmatrix(t_3dmat *m);
void	print_4dmatrix(t_4dmat *m);

t_2dmat	*submat_3d(t_3dmat *matrix, int row, int column);
t_3dmat	*submat_4d(t_4dmat *matrix, int row, int column);
t_4dmat	identity(void);
t_4dmat	transpose(t_4dmat *matrix);

double	determinant(t_2dmat *mat_2d, t_3dmat *mat_3d, t_4dmat *mat_4d);
double	minor_3d(t_3dmat *mat, int row, int column);
double	cofactor_3d(t_3dmat *mat, int row, int column);
double	minor_4d(t_4dmat *mat, int row, int column);
double	cofactor_4d(t_4dmat *mat, int row, int column);

t_4dmat	*create_4dcofactor(t_4dmat *mat);
t_bool	inverse_mat(t_4dmat *mat, t_4dmat *ptr);

t_bool	mat4d_cmp(t_4dmat *mat_one, t_4dmat *mat_two);

t_4dmat	mat4d_mult(t_4dmat *one, t_4dmat *two);
t_tuple	tuple_mult(t_4dmat *mat, t_tuple *tuple);

void	copy_mat(t_4dmat *mat_one, t_4dmat *mat_two);

t_4dmat	axis_angle(t_tuple orientation, double angle);
t_4dmat	mat4d_cross(t_4dmat *a, t_4dmat *b);

#endif