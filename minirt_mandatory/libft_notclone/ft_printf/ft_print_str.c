/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:42:09 by pipolint          #+#    #+#             */
/*   Updated: 2023/11/29 12:44:21 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*return_null(char *str, int *free_flag)
{
	char	*s;

	s = NULL;
	if (str == NULL)
	{
		*free_flag = 1;
		s = malloc((sizeof(char) * ft_strlen("(null)") + 1));
		if (!s)
			return (NULL);
		ft_strlcpy(s, "(null)", ft_strlen("(null)") + 1);
		str = s;
	}
	return (str);
}

void	ft_print_str(char *str, int *written, t_flags *f)
{
	int		need_free;
	int		len;
	int		zero_prec;

	zero_prec = 0;
	if (!f->p_width && f->is_period)
		zero_prec = 1;
	need_free = 0;
	str = return_null(str, &need_free);
	len = ft_strlen(str);
	if (f->empty_prec)
		f->p_width = 0;
	if ((f->p_width > len || f->p_width == 0 || f->p_width < 0)
		&& !f->empty_prec)
		f->p_width = len;
	if (f->f_width > f->p_width && !f->is_hyphen)
		*written += ft_putchar_n(' ', 1, f->f_width - f->p_width);
	if (!zero_prec)
		*written += write(1, str, f->p_width);
	if (f->f_width > f->p_width && f->is_hyphen)
		*written += ft_putchar_n(' ', 1, f->f_width - f->p_width);
	if (need_free)
		free(str);
}
