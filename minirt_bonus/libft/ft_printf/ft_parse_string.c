/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 01:10:53 by pipolint          #+#    #+#             */
/*   Updated: 2023/11/29 20:39:04 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_check_flags_2(const char *format, t_flags *flags)
{
	if (*format == '.' && !flags->p_width)
	{
		flags->is_period = 1;
		if (!ft_isdigit(*(format + 1)))
			flags->empty_prec = 1;
		flags->p_width = ft_atoi((format + 1));
		if (!flags->p_width)
			flags->empty_prec = 1;
	}
	if (flags->is_space && flags->is_plus)
		flags->is_space = 0;
}

static void	ft_check_flags_1(const char *format, t_flags *flags)
{
	if (*format == '0')
	{
		if (flags->is_hyphen)
			flags->is_zero = 0;
		else if (!flags->f_width && !flags->is_period)
		{
			flags->is_zero = 1;
			flags->f_width = ft_atoi(format);
		}
	}
	if (ft_isdigit(*format) && !flags->f_width && !flags->is_period)
		flags->f_width = ft_atoi(format);
	if (*format == '#')
		flags->is_hash = 1;
	if (*format == '+')
		flags->is_plus = 1;
	if (*format == '-')
		flags->is_hyphen = 1;
	if (*format == ' ' && !flags->is_plus)
		flags->is_space = 1;
	ft_check_flags_2(format, flags);
}

void	ft_parse_string(const char *format, t_flags *flags)
{
	size_t	i;

	i = 0;
	while (format[i] && !ft_is_specifier(format[i]))
	{
		ft_check_flags_1(&format[i], flags);
		i++;
	}
	if (ft_is_specifier(format[i]) || format[i] == '%')
		flags->spec = (unsigned char)format[i];
}
