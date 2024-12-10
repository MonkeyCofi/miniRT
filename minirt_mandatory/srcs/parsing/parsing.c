/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:23:17 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/09 15:00:26 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_camera(t_minirt *minirt, char *string)
{
	char	**str;
	int		i;

	i = 0;
	if (minirt->cam->flag != 0)
		parse_error(minirt, CAM_AMT_ERR, NULL, 1);
	else
		minirt->cam->flag = 1;
	str = ft_split(string, ' ');
	if (arr_len(str) != 4)
		parse_error(minirt, CAM_ARG_ERR, str, 1);
	while (str[i] && str[i++])
	{
		if (i == 1 && !dovector(minirt, str[i], &minirt->from, false))
			parse_error(minirt, CAM_COORD_ERR, str, 1);
		if (i == 2 && !dovector(minirt, str[i], &minirt->to, true))
			parse_error(minirt, CAM_ORIENT_ERR, str, 1);
		if (i == 3 && check_ulong(str[i], &minirt->cam->fov))
			parse_error(minirt, "Camera: Invalid FOV", str, 1);
		minirt->from.w = POINT;
	}
	free_arr(str);
	return (0);
}

static inline int	parse_elements(char *str, t_minirt *m)
{
	char	*line;
	char	*tmp;

	line = NULL;
	if (ft_strncmp(str, "A ", 2) == 0)
		return (parse_ambient(m, str));
	if (ft_strncmp(str, "C ", 2) == 0)
		return (parse_camera(m, str));
	if (ft_strncmp(str, "L ", 2) == 0)
		return (parse_light(m, str));
	else
	{
		line = ft_itoa(m->line);
		if (!line)
			parse_error(m, "itoa: Couldn't allocate memory for string", \
				NULL, 1);
		tmp = ft_strjoin("Invalid element: ", str);
		if (!tmp)
			parse_error(m, "strjoin: Couldn't allocate memory for string", \
				NULL, 1);
		write_error(m, tmp, line, 0);
		free(tmp);
		return (1);
	}
}

static inline int	parsing_sphere(char *str, t_minirt *m, int *i)
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
	return (1);
}

int	parsing(char *str, t_minirt *minirt, int *i)
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
	if (parsing_sphere(str, minirt, i) == 0)
		return (0);
	return (parse_elements(str, minirt));
}

int	getmap(int fd, t_minirt *minirt, int i)
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
		if (parsing(line, minirt, &i) == 1)
			ret = 1;
		free(line);
	}
	close(fd);
	if (!ret && (invalidfile(minirt) != 1))
		parse_error(minirt, "Missing elements", NULL, 0);
	return (ret);
}
