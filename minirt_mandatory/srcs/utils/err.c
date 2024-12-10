/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:27:27 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/10 15:29:32 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	write_check(t_minirt *m, char *str)
{
	if (write(2, str, ft_strlen(str)) == -1)
		free_minirt(m, 1);
}

void	write_error(t_minirt *m, char *error_line, char *line_number, int should_exit)
{
	write_check(m, "Error\n");
	write_check(m, error_line);
	write_check(m, "\n");
	if (line_number)
	{
		write_check(m, "Line: ");
		write_check(m, line_number);
		write_check(m, "\n");
		free(line_number);
	}
	if (should_exit)
		free_minirt(m, EXIT_FAILURE);
}

void	write_two_errs(t_minirt *m, char *str1, int need_newline, char *str2)
{
	if (str1 && write(2, str1, ft_strlen(str1)) == -1)
		free_minirt(m, 1);
	if (need_newline)
		write_check(m, "\n");
	if (str2 && write(2, str2, ft_strlen(str2)) == -1)
		free_minirt(m, 1);
}

void	parse_error(t_minirt *m, char *err, char **parse_arr, int print_line_num)
{
	char	*line_no;

	free_arr(parse_arr);
	line_no = NULL;
	if (print_line_num)
	{
		line_no = ft_itoa(m->line);
		if (!line_no)
		{
			write_check(m, "Error\nCannot allocate memory for string\n");
			free_arr(parse_arr);
			free_minirt(m, 1);
		}
	}
	write_error(m, err, line_no, 1);
}
