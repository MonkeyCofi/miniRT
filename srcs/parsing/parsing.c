/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:23:17 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/03 20:08:42 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_camera(t_minirt *minirt, char *string)
{
	char	**str;
	int		i;

	i = 0;
	if (minirt->cam->flag != 0)
		parse_error(minirt, "Error: Camera: You can only have one camera", string, NULL);
	else
		minirt->cam->flag = 1;
	str = ft_split(string, ' ');
	if (arr_len(str) != 4)
		parse_error(minirt, "Error: Camera: Invalid number of arguments", string, str);
	while (str[i] && str[i++])
	{
		if (i == 1 && dovector(str[i], &minirt->from, false) == false)
			parse_error(minirt, "Error: Camera: Invalid coordinates", string, str);
		if (i == 2 && dovector(str[i], &minirt->to, true) == false)
			parse_error(minirt, "Error: Camera: Invalid orientation", string, str);
		if (i == 3 && check_ulong(str[i], &minirt->cam->fov))
			parse_error(minirt, "Error: Camera: Invalid FOV", string, str);
		minirt->from.w = POINT;
	}
	free_arr(str);
	return (0);
}

static inline int	parse_elements(char *str, t_minirt *m, int *j)
{
	char	*line;

	line = NULL;
	if (ft_strncmp(str, "A", 1) == 0)
		return (parse_ambient(m, str));
	if (ft_strncmp(str, "C", 1) == 0)
		return (parse_camera(m, str));
	if (ft_strncmp(str, "L", 1) == 0)
		return (parse_light(m, str, j));
	else
	{
		write_two_errs(m, "Error: Invalid element", 1, "Line number: ", 0);
		line = ft_itoa(m->line);
		if (!line)
		{
			parse_error(m, "Error: itoa: Couldn't allocate memory for string", \
				NULL, NULL);
		}
		write_two_errs(m, line, 1, NULL, 0);
		write_two_errs(m, "Line: ", 0, str, 1);
		free(line);
		return (1);
	}
}

static inline int	parsing_sp_co(char *str, t_minirt *m, int *i)
{
	if (ft_strncmp(str, "sp", 2) == 0)
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
	if (ft_strncmp(str, "co", 2) == 0)
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
	if (ft_strncmp(str, "pl", 2) == 0)
		return (parse_plane(minirt, str, i));
	if (ft_strncmp(str, "cy", 2) == 0)
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
