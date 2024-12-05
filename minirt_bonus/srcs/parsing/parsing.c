/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:23:17 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/05 20:34:03 by pipolint         ###   ########.fr       */
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
		write_two_errs(m, "Error: Invalid element", 1, "Line number: ");
		line = ft_itoa(m->line);
		if (!line)
		{
			parse_error(m, "Error: itoa: Couldn't allocate memory for string", \
				NULL, NULL);
		}
		write_two_errs(m, line, 1, NULL);
		write_two_errs(m, "Line: ", 0, str);
		write_check(m, "\n");
		free(line);
		return (1);
	}
}

static inline int	parsing_sp_co(char *str, t_minirt *m, int *i)
{
	if (ft_strncmp(str, "sp ", 3) == 0)
	{
		if (parse_sphere(m, str, i) == 0)
		{
			m->object_count++;
			*i += 1;
			return (0);
		}
		else
			return (1);
	}
	if (ft_strncmp(str, "co ", 3) == 0)
	{
		if (parse_cone(m, str, i) == 0)
		{
			m->shapes[*i]->type = CONE;
			m->object_count += 1;
			*i += 1;
			return (0);
		}
		else
			return (1);
	}
	return (1);
}

int	parsing(char *str, t_minirt *minirt, int *i, int *j)
{
	if (ft_strncmp(str, "#", 1) == 0)
		return (0);
	if (ft_strncmp(str, "pl ", 3) == 0)
		return (parse_plane(minirt, str, i));
	if (ft_strncmp(str, "cy ", 3) == 0)
	{
		if (parse_cylinder(minirt, str, i) == 0)
		{
			minirt->shapes[*i]->type = CYLINDER;
			minirt->object_count += 1;
			*i += 1;
			return (0);
		}
		else
			return (1);
	}
	if (parsing_sp_co(str, minirt, i) == 0)
		return (0);
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
	close(fd);
	if (!ret && (invalidfile(minirt) != 1))
		parse_error(minirt, "Error: Missing elements", NULL, NULL);
	return (ret);
}
