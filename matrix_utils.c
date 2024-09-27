/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:54:54 by pipolint          #+#    #+#             */
/*   Updated: 2024/09/27 18:01:53 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//t_3dmat	*create_3dmat()
//{

//}

void	print_3dmatrix(t_3dmat *m)
{
	printf("%.5f ", m->m11);
	printf("%.5f ", m->m12);
	printf("%.5f\n", m->m13);
	printf("%.5f ", m->m21);
	printf("%.5f ", m->m22);
	printf("%.5f\n", m->m23);
	printf("%.5f ", m->m31);
	printf("%.5f ", m->m32);
	printf("%.5f\n", m->m13);
}
void	print_matrix(t_4dmat *m)
{
	printf("%.5f ", m->m11);
	printf("%.5f ", m->m12);
	printf("%.5f ", m->m13);
	printf("%.5f\n", m->m14);
	printf("%.5f ", m->m21);
	printf("%.5f ", m->m22);
	printf("%.5f ", m->m23);
	printf("%.5f\n", m->m24);
	printf("%.5f ", m->m31);
	printf("%.5f ", m->m32);
	printf("%.5f ", m->m33);
	printf("%.5f\n", m->m34);
	printf("%.5f ", m->m41);
	printf("%.5f ", m->m42);
	printf("%.5f ", m->m43);
	printf("%.5f\n", m->m44);
}