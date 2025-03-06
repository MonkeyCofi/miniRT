/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 22:09:29 by pipolint          #+#    #+#             */
/*   Updated: 2023/11/30 11:16:15 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_ishash(t_flags *f)
{
	if (f->spec == 'x')
		return ("0x");
	return ("0X");
}

char	*return_hexa_nbr(unsigned int n, int *length, t_flags *f)
{
	char	*nbr;

	if (f->spec == 'x')
		nbr = ft_itoa_ubase(n, "0123456789abcdef");
	else
		nbr = ft_itoa_ubase(n, "0123456789ABCDEF");
	*length = ft_strlen(nbr);
	return (nbr);
}

void	ft_print_hexa(va_list args, int *written, t_flags *f)
{
	char			*nbr;
	unsigned int	n;
	int				length;

	n = va_arg(args, unsigned int);
	nbr = return_hexa_nbr(n, &length, f);
	if (!f->p_width || f->p_width < length)
		f->p_width = length;
	if (f->empty_prec && nbr[0] == '0')
		f->p_width = 0;
	f->f_width -= 2 * (f->is_hash && n);
	if (f->f_width > f->p_width && !f->is_hyphen \
		&& (!f->is_zero || f->is_period))
		*written += ft_putchar_n(' ', 1, f->f_width - f->p_width);
	if (f->is_hash && n)
		*written += ft_putstr(ft_ishash(f), 1, 2);
	if (f->is_zero && f->f_width > f->p_width && !f->is_hyphen && !f->is_period)
		*written += ft_putchar_n('0', 1, f->f_width - f->p_width);
	else if (f->is_period)
		*written += ft_putchar_n('0', 1, f->p_width - length);
	if (f->p_width)
		*written += ft_putstr(nbr, 1, length);
	if (f->is_hyphen)
		*written += ft_putchar_n(' ', 1, f->f_width - f->p_width);
	free(nbr);
}
