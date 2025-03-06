/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_addr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:21:20 by pipolint          #+#    #+#             */
/*   Updated: 2023/11/30 11:37:46 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_addr(va_list args, int *written, t_flags *f)
{
	unsigned long	n;
	void			*addr;
	char			*nbr;
	char			*temp;
	int				len;

	addr = va_arg(args, void *);
	n = (unsigned long)addr;
	temp = ft_itoa_ubase(n, "0123456789abcdef");
	nbr = ft_strjoin("0x", temp);
	free(temp);
	len = ft_strlen(nbr);
	if (f->p_width > len || !f->p_width || f->p_width < 0)
		f->p_width = len;
	if (f->f_width > f->p_width && !f->is_hyphen)
		*written += ft_putchar_n(' ', 1, f->f_width - f->p_width);
	*written += write(1, nbr, f->p_width);
	if (f->f_width > f->p_width && f->is_hyphen)
		*written += ft_putchar_n(' ', 1, f->f_width - f->p_width);
	free(nbr);
}
