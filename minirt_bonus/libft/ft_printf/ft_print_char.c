/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:18:33 by pipolint          #+#    #+#             */
/*   Updated: 2023/11/23 14:37:49 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_char(char c, int *written, t_flags *flags)
{
	flags->p_width = 1;
	if (flags->is_zero && flags->f_width)
		*written += ft_putchar_n('0', 1, flags->f_width - flags->p_width);
	if (flags->f_width && !flags->is_hyphen && !flags->is_zero)
		*written += ft_putchar_n(' ', 1, flags->f_width - flags->p_width);
	*written += ft_putchar_n(c, 1, flags->p_width);
	if (flags->is_hyphen && flags->f_width)
		*written += ft_putchar_n(' ', 1, flags->f_width - flags->p_width);
}
