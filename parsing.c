/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:23:17 by ahaarij           #+#    #+#             */
/*   Updated: 2024/08/22 10:31:07 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"
#include <string.h>

int	parsing(char *str)
{
	if (strncmp(str, "A", 1) == 0)
		return (0);
		// return parse ambient lighting god i hate parsing
	else if(strncmp(str, "C", 1) == 0)
		return (0);
		// return parse camera
	else if(strncmp(str, "L", 1) == 0)
		// return parse lighting (normal version)
		return (0);
	// return parse sphere
	else if (strncmp(str, "sp", 2) == 0)
		return (0);
	// else if (strncmp(str, " ", 1) == 0)
	// 	return (1);
	// printf("str broke %s\n", str);
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

int	getmap(int fd)
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
		
		if (parsing(line) == 1)
			ret = 1;
		printf("str <<<<%s>>>> ret %d\n", line, ret);
		free(line);
	}
	if (!ret) // need to check if we have certain things, like camera and light
		ret = 1;
	close(fd);
	return (ret);
}

int	fileopen(char *path)
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
	if(getmap(fd))
		return (0);
	return (1);
}