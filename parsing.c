/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:23:17 by ahaarij           #+#    #+#             */
/*   Updated: 2024/10/23 14:55:33 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"
#include <string.h>

int	dovector(char *string, t_tuple *calc)
{
	char	**str;
	int		i;
	int		ret;
	
	i = -1;
	ret = 0;
	str = ft_split(string, ',');
	while (str && str[++i])
	{
		if (!is_double(str[i]))
			ret = 1;
	}
	if (arr_len(str) != 3)
		ret = 1;
	else
	{
		calc->x = str_to_double(str[0]) / 100.0;
		calc->y = str_to_double(str[1]) / 100.0;
		calc->z = str_to_double(str[2]) / 100.0;
	}
	free_arr(str);
	return (ret);
}

int	dovectorcolor(char *string, t_tuple *calc)
{
	char	**str;
	int		i;
	int		ret;
	
	i = -1;
	ret = 0;
	str = ft_split(string, ',');
	(void)calc;
	while (str && str[++i])
	{
		if (!is_double(str[i]))
			ret = 1;
	}
	if (arr_len(str) != 3)
		ret = 1;
	else
	{
		calc->x = str_to_double(str[0]) / 255.0;
		calc->y = str_to_double(str[1]) / 255.0;
		calc->z = str_to_double(str[2]) / 255.0;
	}
	free_arr(str);
	return (ret);
}

int	isulong(char *str)
{
	int i = 0;
	while (str && str[i])
	{
		if (ft_isdigit(str[i]) != 1)
			return (0);
		i++;
	}
	return (1);
}

int	check_ulong(char *str, int *num)
{
	if(!isulong(str))
		return (1);
	*num = ft_atoi(str);
	if(*num > 180)
		return (1);
	return (0);
}

int	check_double(char *str, double *num)
{
	if(!is_double(str))
	{
		printf("parameter is not a double\n");
		return (1);
	}
	*num = str_to_double(str);
	return (0);
}

int	parse_camera(t_minirt *minirt, char *string)
{
	char	**str;
	int 	i;

	i = 0;
	str = ft_split(string, ' ');
	if(minirt->cam->flag != false)
		return (1);
	else
		minirt->cam->flag = true;
	if(arr_len(str) != 4)
		return (1);
	while(string && string[i++])
	{
		if (i == 1 && dovector(str[i], &minirt->cam->camera))
			return (1);
		if (i == 2 && dovector(str[i], &minirt->cam->orientation))
			return (1);
		if (i == 3 && check_ulong(str[i], &minirt->cam->h_fov))
			return (1);
	}
	free_arr(str);
	return (0);
}

int	parse_sphere(t_minirt *minirt, char *string)
{
	int 	i;
	char	**str;

	str = ft_split(string, ' ');
	i = 1;
	if(arr_len(str) != 4)
		return (1);
	while (string && string[i])
	{
		if (i == 1 && dovector(str[i], &minirt->spheres->center))
			return (1);
		if (i == 2 && check_double(str[i], &minirt->spheres->radius))
			return (1);
		if (i == 3 && dovectorcolor(str[i], &minirt->spheres->color))
			return (1);
		i++;
	}
	free_arr(str);
	printf("x y z %f %f %f\n", minirt->spheres->center.x, minirt->spheres->center.y, minirt->spheres->center.z);
	minirt->spheres->radius /= 2;
	return (0);
}

int	parsing(char *str, t_minirt *minirt)
{
	if (strncmp(str, "sp", 2) == 0)
	{
		return (parse_sphere(minirt, str));
	}
	if (strncmp(str, "A", 1) == 0)
		return (0);
	if (strncmp(str, "C", 1) == 0)
		return (parse_camera(minirt, str));
	if (strncmp(str, "L", 1) == 0)
		return (0);
	else
		return (1);
}

int	rt_file(char *str)
{
	int len;

	len = ft_strlen(str) - 3;	
	if(len > 3)
		return ((ft_strncmp((str + len), ".rt", 3) == 0));
	return (0);
}


char	*trimline(char *str)
{
	int 	i;
	char	*temp;

	i = -1;
	temp = str;
	while(temp && temp[++i])
	{
		if(temp[i] == '\t' || temp[i] == '\n')
			temp[i] = ' ';
	}
	str = ft_strtrim(temp, " ");
	free(temp);
	return (str);
}

int	getmap(int fd, t_minirt *minirt)
{
	int ret;
	char *line;

	ret = 0;
	while (ret != 1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (strncmp(line, "\n", 1) == 0)
		{
			free(line);
			continue;
		}
		line = trimline(line);
		if (parsing(line, minirt) == 1)
			ret = 1;
		free(line);
	}
	// if (!ret && invalidfile) // need to check if we have certain things, like camera and light
	// 	ret = 1;
	close(fd);
	return (ret);
}

int	fileopen(char *path, t_minirt *minirt)
{

	int fd;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("error message should be here lol, ig we'll make a function for exiting");
		return (1);
	}
	if (!rt_file(path))
	{
		printf("Another error message, this one for the fact that its not a rt file");
		return (1);
	}
	if (getmap(fd, minirt) == 1){
		printf("Invalid File\n");
		return (1);
	}
	return (0);
}