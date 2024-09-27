/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:48:13 by pipolint          #+#    #+#             */
/*   Updated: 2024/09/27 18:03:41 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "structs.h"

t_3dmat	*create_3dmat();
t_3dmat	*create_4dmat();
void	print_3dmatrix(t_3dmat *m);
void	print_4dmatrix(t_4dmat *m);

#endif