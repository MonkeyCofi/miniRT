/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:23:17 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/10 11:49:53 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline int	parse_elements(char *str, t_minirt *m, int *j)
{
	char	*line;

	line = NULL;
	if (ft_strncmp(str, "A ", 2) == 0)
		return (parse_ambient(m, str));
	if (ft_strncmp(str, "C ", 2) == 0)
		return (parse_camera(m, str));
	if (ft_strncmp(str, "L ", 2) == 0)
		return (parse_light(m, str, j));
	else
	{
		write_check(m, "Error\nInvalid element\n");
		write_check(m, "Line number: ");
		line = ft_itoa(m->line);
		if (!line)
			parse_error(m, "itoa: Couldn't allocate memory for string", \
				NULL, 0);
		write_check(m, line);
		write_check(m, "\n");
		free(line);
		return (1);
	}
}

static inline int	parsing_sp_co(char *str, t_minirt *m, int *i)
{
	if (ft_strncmp(str, "sp ", 3) == 0)
	{
		m->object_count++;
		if (parse_sphere(m, str, i) == 0)
		{
			*i += 1;
			return (0);
		}
		else
			return (write_and_return(m, "Error\nInvalid sphere parameters\n", 1));
	}
	else if (ft_strncmp(str, "co ", 3) == 0)
	{
		m->object_count += 1;
		if (parse_cone(m, str, i) == 0)
		{
			m->shapes[*i]->type = CONE;
			*i += 1;
			return (0);
		}
		else
			return (write_and_return(m, "Error\nInvalid cone parameters\n", 1));
	}
	return (-1);
}

int	parsing(char *str, t_minirt *minirt, int *i, int *j)
{
	int ret;

	if (ft_strncmp(str, "#", 1) == 0)
		return (0);
	if (ft_strncmp(str, "pl ", 3) == 0)
		return (parse_plane(minirt, str, i));
	if (ft_strncmp(str, "cy ", 3) == 0)
	{
		minirt->object_count++;
		if (parse_cylinder(minirt, str, i) == 0)
		{
			minirt->shapes[*i]->type = CYLINDER;
			*i += 1;
			return (0);
		}
		else
			return (write_and_return(minirt, "Error\nInvalid cylinder parameters\n", 1));
	}
	ret = parsing_sp_co(str, minirt, i);
	if (ret == 0)
		return (0);
	else if (ret == 1)
		return (write_and_return(minirt, "", 1));
	return (parse_elements(str, minirt, j));
}

int	getmap(int fd, t_minirt *minirt, int i, int j)
{
	int		ret;
	char	*line;

	ret = 0;
	minirt->line = 0;
	while (ret != 1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		minirt->line++;
		if (ft_strncmp(line, "\n", 1) == 0)
		{
			free(line);
			continue ;
		}
		line = trimline(line);
		if (parsing(line, minirt, &i, &j) == 1)
			ret = 1;
		free(line);
	}
	if (ret == 1)
		free_minirt(minirt, EXIT_FAILURE);
	close(fd);
	if (!ret && (invalidfile(minirt) != 1))
		parse_error(minirt, "Missing elements", NULL, 0);
	return (ret);
}
