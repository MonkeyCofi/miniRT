/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:23:17 by ahaarij           #+#    #+#             */
/*   Updated: 2024/08/23 13:03:37 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"
#include <string.h>

int	dovector(char *string, t_vector *calc)
{
	char	**str;
	int		i = -1;
	int		ret = 0;
	str = ft_split(string, ',');
	while(str && str[++i])
		if(!is_float(str[i]))
			ret = 1;
	if(arr_len(str) != 3)
		ret = 1;
	else
	{
		calc->x = str_to_double(str[0]);
		calc->y = str_to_double(str[1]);
		calc->z = str_to_double(str[2]);
	}
	free_arr(str);
	return (ret);
}

int	parse_camera(t_cameraparse *cam, char *string)
{
	char	**str;
	int i = 0;
	
	str = ft_split(string, ' ');
	if(cam->flag != 0)
		return (1);
	else
		cam->flag = 1;
	if(arr_len(str) != 4)
		return (1);
	while(string && string[i++])
	{
		if (i == 1 && dovector(str[i], &cam->campos))
			return (1);
		if (i == 2 && dovector(str[i], &cam->vec))
			return (1);
		// if (i == 3 && dovectorbutlikeforfov(str[i], &cam->fov))
		// 	return (1);
	}
	// in our main struct make something that calls t_camera so we can just minirt->cam = camera;
	free_arr(str);
	return (0);
}

int	parsing(char *str, t_cameraparse *cam)
{
	if (strncmp(str, "A", 1) == 0)
		return (0);
	else if(strncmp(str, "C", 1) == 0)
		return (parse_camera(cam, str));
	else if(strncmp(str, "L", 1) == 0)
		return (0);
	else if (strncmp(str, "sp", 2) == 0)
		return (0);
	else
		return (1);
}

int	rt_file(char *str)
{
	int len;

	len = ft_strlen(str) - 3;	
	if(len > 3)
		return((ft_strncmp((str + len), ".rt", 3) == 0));
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

int	getmap(int fd, t_cameraparse *cam)
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
		// printf("<<<<<<<<<<<<<<<<<<<<<%s>>>>>>>>>>>>>>>>>>>>>\n", line);
		
		/* need to put a function with a whole bunch of ftstrcmps
		like if (ftstrcmp blah blah == 0)
		do dis and put it in a struct? ya struct
		ret = 1 if parse habbens */
		
		if (parsing(line, cam) == 1)
			ret = 1;
		printf("str <<<<%s>>>> ret %d\n", line, ret);
		free(line);
	}
	// if (!ret && invalidfile) // need to check if we have certain things, like camera and light
	// 	ret = 1;
	close(fd);
	return (ret);
}

int	fileopen(char *path, t_cameraparse *cam)
{

	int fd;
	fd = open(path, O_RDONLY);
	if(fd == -1)
	{
		printf("error message should be here lol, ig we'll make a function for exiting");
		return (1);
	}
	if(!rt_file(path))
	{
		printf("Another error message, this one for the fact that its not a rt file");
		return (1);
	}
	if(getmap(fd, cam) == 1)
		return (1);
	return (0);
}