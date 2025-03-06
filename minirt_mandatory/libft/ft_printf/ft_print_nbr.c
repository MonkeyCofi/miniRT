/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 21:29:12 by pipolint          #+#    #+#             */
/*   Updated: 2023/11/30 11:17:41 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	set_negative_nbr(int n, t_flags *f)
{
	if (n < 0)
	{
		f->is_negative = 1;
		n *= -1;
	}
	return (n);
}

static char	return_sign(t_flags *f)
{
	if (f->is_plus && !f->is_negative)
		return ('+');
	return ('-');
}

static void	ft_print_flags(char *nbr, int *written, int length, t_flags *f)
{
	int	wrote_space;

	wrote_space = 0;
	if (f->empty_prec && nbr[0] == '0')
		f->p_width = 0;
	f->f_width -= ((f->is_negative || f->is_plus) && f->f_width);
	if (f->is_space && !f->is_negative && !f->is_plus)
	{
		*written += ft_putchar_n(' ', 1, 1);
		wrote_space = 1;
	}
	if (f->f_width && !f->is_zero && !f->is_hyphen)
		*written += ft_putchar_n(' ', 1, f->f_width - f->p_width - wrote_space);
	if (f->is_plus || f->is_negative)
		*written += ft_putchar_n(return_sign(f), 1, 1);
	if (f->is_period)
		*written += ft_putchar_n('0', 1, f->p_width - length);
	if (f->is_zero && !f->is_period)
		*written += ft_putchar_n('0', 1, f->f_width - f->p_width - wrote_space);
	if (f->p_width)
		*written += write(1, nbr, length);
	if (f->is_hyphen && !f->is_zero)
		*written += ft_putchar_n(' ', 1, f->f_width - f->p_width - wrote_space);
}

void	ft_print_nbr(va_list args, int *written, t_flags *f)
{
	char	*nbr;
	int		n;

	if (f->spec == 'u')
		nbr = ft_itoa_ubase(va_arg(args, unsigned int), "0123456789");
	else
	{
		n = va_arg(args, int);
		n = set_negative_nbr(n, f);
		if (n == -2147483648)
			nbr = ft_strdup("2147483648");
		else
			nbr = ft_itoa(n);
	}
	if (f->p_width < (int)ft_strlen(nbr) || !f->p_width)
		f->p_width = ft_strlen(nbr);
	if (f->is_zero && f->is_period)
		f->is_zero = 0;
	ft_print_flags(nbr, written, ft_strlen(nbr), f);
	free(nbr);
}
