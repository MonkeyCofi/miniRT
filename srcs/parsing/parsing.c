/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:23:17 by ahaarij           #+#    #+#             */
/*   Updated: 2024/11/29 21:05:21 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_rest(char *str, t_minirt *m, int *j)
{
	if (strncmp(str, "A", 1) == 0)
		return (parse_ambient(m, str));
	if (strncmp(str, "C", 1) == 0)
		return (parse_camera(m, str));
	if (strncmp(str, "L", 1) == 0)
		return (parse_light(m, str, j));
	else
	{
		printf("Error At Line :\n%s\n", str);
		return (1);
	}
}

int	parsing_norminette(char *str, t_minirt *m, int *i)
{
	if (strncmp(str, "sp", 2) == 0)
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
	if (strncmp(str, "co", 2) == 0)
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
	if (strncmp(str, "#", 1) == 0)
		return (0);
	if (strncmp(str, "pl", 2) == 0)
		return (parse_plane(minirt, str, i));
	if (strncmp(str, "cy", 2) == 0)
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
	if (parsing_norminette(str, minirt, i) == 0)
		return (0);
	return (parse_rest(str, minirt, j));
}

int	getmap(int fd, t_minirt *minirt, int i, int j)
{
	int		ret;
	char	*line;

	ret = 0;
	while (ret != 1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (strncmp(line, "\n", 1) == 0)
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
		return (printf("Error\nMissing Necessary Element\n"), 1);
	return (ret);
}

int	fileopen(char *path, t_minirt *minirt)
{
	int	fd;
	int	i;
	int	j;

	i = 0;
	j = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nFailed to open file!\n");
		return (close(fd), 1);
	}
	if (!rt_file(path))
	{
		printf("Error\nNot a rt file!\n");
		return (close(fd), 1);
	}
	if (getmap(fd, minirt, i, j) == 1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
