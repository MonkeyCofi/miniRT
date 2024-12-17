/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:07:14 by pipolint          #+#    #+#             */
/*   Updated: 2023/12/07 12:04:41 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	do_op(va_list args, int *written, t_flags *f)
{
	if (f->spec == 'c')
		ft_print_char(va_arg(args, unsigned int), written, f);
	else if (f->spec == 's')
		ft_print_str(va_arg(args, char *), written, f);
	else if (f->spec == 'p')
		ft_print_addr(args, written, f);
	else if (f->spec == 'd' || f->spec == 'i')
		ft_print_nbr(args, written, f);
	else if (f->spec == 'u')
		ft_print_nbr(args, written, f);
	else if (f->spec == 'x')
		ft_print_hexa(args, written, f);
	else if (f->spec == 'X')
		ft_print_hexa(args, written, f);
	else if (f->spec == '%')
		ft_print_char('%', written, f);
}

static void	init_list(t_flags *lst)
{
	(*lst).f_width = 0;
	(*lst).is_hash = 0;
	(*lst).is_hyphen = 0;
	(*lst).is_period = 0;
	(*lst).is_plus = 0;
	(*lst).is_space = 0;
	(*lst).is_zero = 0;
	(*lst).p_width = 0;
	(*lst).spec = 0;
	(*lst).is_negative = 0;
	(*lst).empty_prec = 0;
}

static int	do_print(const char *format, va_list args, t_flags *flags)
{
	size_t	i;
	int		written;

	i = 0;
	written = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			i++;
			ft_parse_string(&format[i], flags);
			if (flags->f_width == 2147483647 || flags->p_width == 2147483647
				|| flags->f_width == -2147483648
				|| flags->p_width == -2147483648)
				return (-1);
			do_op(args, &written, flags);
			while (!ft_is_specifier(format[i]) && format[i])
				i++;
		}
		else
			written += write(1, &format[i], 1);
		init_list(flags);
		i++;
	}
	return (written);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	t_flags	flags;
	int		written;

	init_list(&flags);
	written = 0;
	va_start(args, format);
	written = do_print(format, args, &flags);
	va_end(args);
	return (written);
}
