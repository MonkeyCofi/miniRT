/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:32:59 by pipolint          #+#    #+#             */
/*   Updated: 2023/12/21 14:13:40 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include "..//libft.h"

typedef struct s_flags
{
	int	spec;
	int	is_hyphen;
	int	is_zero;
	int	is_period;
	int	is_hash;
	int	is_space;
	int	is_plus;
	int	f_width;
	int	p_width;
	int	empty_prec;
	int	is_negative;
}	t_flags;

int		ft_printf(const char *format, ...);
void	ft_parse_string(const char *format, t_flags *flags);
int		ft_is_specifier(char c);
void	ft_print_char(char c, int *written, t_flags *flags);
int		ft_putchar_n(char c, int fd, int amount);
void	ft_print_str(char *str, int *written, t_flags *flags);
void	ft_print_nbr(va_list args, int *written, t_flags *flags);
char	*ft_itoa_ubase(unsigned long n, char *base);
int		ft_putstr(char *str, int fd, int n);
void	ft_print_hexa(va_list args, int *written, t_flags *f);
void	ft_print_addr(va_list args, int *written, t_flags *f);

#endif