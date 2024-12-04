/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:27:27 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/04 22:06:12 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	write_check(t_minirt *m, char *str)
{
	if (write(2, str, ft_strlen(str)) == -1)
		free_minirt(m);
}

void	write_two_errs(t_minirt *m, char *str1, int need_newline, char *str2)
{
	if (str1 && write(2, str1, ft_strlen(str1)) == -1)
		free_minirt(m);
	if (need_newline)
	{
		write_check(m, "\n");
	}
	if (str2 && write(2, str2, ft_strlen(str2)) == -1)
		free_minirt(m);
}

void	parse_error(t_minirt *m, char *err, char *line, char **parse_arr)
{
	char	*line_no;

	line_no = NULL;
	line_no = ft_itoa(m->line);
	if (!line_no)
	{
		write_check(m, "Error: Cannot allocate memory for string\n");
		free_arr(parse_arr);
		free_minirt(m);
	}
	write_two_errs(m, err, 1, "Line number: ");
	write_two_errs(m, NULL, 0, line_no);
	write_check(m, "\n");
	if (line)
	{
		write_check(m, "Line: ");
		write_err(line, '\n');
	}
	if (line_no)
		free(line_no);
	free_arr(parse_arr);
	free_minirt(m);
}
