/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:23:17 by ahaarij           #+#    #+#             */
/*   Updated: 2024/11/19 09:11:08 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	recognizespecular(char *string, t_mater *material)
{
	int i;
	i = -1;
	char **str;
	if(ft_strncmp(string, "specular=default", 16) == 0)
		return (0);
	str = ft_split(string, '=');
	if(arr_len(str) != 2)
		return (1);
	while(str && str[++i])
	{
		if (i == 0 && ft_strncmp(str[i], "specular", 8) != 0)
			return(printf("Error\nIssue Lies in Specular Keyword\n"), 1);
		if (i == 1 && check_double(str[i], &material->specular))
			return(printf("Error\nIssue Lies in Specular Value\n"), 1);
	}
	free_arr(str);
	return (0);
}

int	recognizediffuse(char *string, t_mater *material)
{
	int i;
	i = -1;
	char **str;
	if(ft_strncmp(string, "diffuse=default", 15) == 0)
		return (0);
	str = ft_split(string, '=');
	if(arr_len(str) != 2)
		return (1);
	while(str && str[++i])
	{
		if (i == 0 && ft_strncmp(str[i], "diffuse", 7) != 0)
			return(printf("Error\nIssue Lies in Diffuse Keyword\n"), 1);
		if (i == 1 && check_double(str[i], &material->diffuse))
			return(printf("Error\nIssue Lies in Diffuse Value\n"), 1);
	}
	free_arr(str);
	return (0);
}

int	recognizeambient(char *string, t_mater *material)
{
	int i;
	i = -1;
	char **str;
	if(ft_strncmp(string, "ambient=default", 15) == 0)
		return (0);
	str = ft_split(string, '=');
	if(arr_len(str) != 2)
		return (1);
	while(str && str[++i])
	{
		if (i == 0 && ft_strncmp(str[i], "ambient", 8) != 0)
			return(printf("Error\nIssue Lies in Ambient Keyword\n"), 1);
		if (i == 1 && check_double(str[i], &material->ambient))
			return(printf("Error\nIssue Lies in Ambient Value\n"), 1);
	}
	free_arr(str);
	return (0);
}

int	recognizepattern(char *string, t_mater *material)
{
	int i;
	i = -1;
	char **str;
	if(ft_strncmp(string, "pattern=no", 10) == 0)
		return (0);
	str = ft_split(string, '=');
	if(arr_len(str) != 2)
		return (1);
	while(str && str[++i])
	{
		if(i == 0 && ft_strncmp(str[i], "pattern", 7) != 0)
			return(printf("Error\nIssue Lies in Pattern Keyword\n"), 1);
		if(i == 1 && dovectorcolor(str[i], &material->pattern.color_two))
			return(printf("Error\nIssue Lies in Pattern Color\n"), 1);
	}
	free_arr(str);
	material->is_patterned = true;
	material->pattern.color_one = material->color;
	return (0);
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

int	check_ulong(char *str, double *num)
{
	if(!isulong(str))
		return (1);
	*num = ft_atoi(str);
	if(*num > 180 || *num < 0)
		return (1);
	return (0);
}

int	check_double(char *str, double *num)
{
	if(!is_double(str))
		return (1);
	*num = str_to_double(str);
	return (0);
}

int	parse_camera(t_minirt *minirt, char *string)
{
	char	**str;
	int 	i;

	i = 0;
	if(minirt->cam->flag != 0)
		return (1);
	else
		minirt->cam->flag = 1;
	str = ft_split(string, ' ');
	if(arr_len(str) != 4)
		return (1);
	while(str[i] && str[i++])
	{
		if (i == 1 && dovector(str[i], &minirt->from))
			return (printf("Error\nIssue Lies in Camera Coordinates\n"), 1);
		if (i == 2 && dovectororientationf(str[i], &minirt->to))
			return (printf("Error\nIssue Lies in Camera Orientation\n"), 1);
		if (i == 3 && check_ulong(str[i], &minirt->cam->fov))
			return (printf("Error\nIssue Lies in Camera FOV\n"), 1);
		minirt->from.w = POINT;
	}
	free_arr(str);
	return (0);
}

int	parsing(char *str, t_minirt *minirt, int *i, int *j)
{
	if(strncmp(str, "#", 1) == 0)
		return (0);
	if (strncmp(str, "sp", 2) == 0)
		return (parse_sphere(minirt, str, i));
	if (strncmp(str, "pl", 2) == 0)
		return (parse_plane(minirt, str, i));
	if (strncmp(str, "cy", 2) == 0)
		return (parse_cylinder(minirt, str, i));
	if (strncmp(str, "co", 2) == 0)
		return (parse_cone(minirt, str, i));
	if (strncmp(str, "A", 1) == 0)
		return (parse_ambient(minirt, str));
	if (strncmp(str, "C", 1) == 0)
		return  (parse_camera(minirt, str));
	if (strncmp(str, "L", 1) == 0)
		return (parse_light(minirt, str, j));
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

int	invalidfile(t_minirt *minirt)
{
	if(minirt->ambient->flag == 1 && minirt->cam->flag == 1 && minirt->light_count > 0)
		return (1);
	return (0);
}

int	getmap(int fd, t_minirt *minirt)
{
	int ret;
	char *line;
	int i = 0;
	int j = 0;

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
		if (parsing(line, minirt, &i, &j) == 1)
		{
			printf("%s\n", line);
			ret = 1;
		}
		free(line);
	}
	close(fd);
	if (!ret && (invalidfile(minirt) != 1))
		return(printf("Error\nMissing Necessary Element\n"), 1);
	return (ret);
}

int	fileopen(char *path, t_minirt *minirt)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nFailed to open file!\n");
		close(fd);
		return (1);
	}
	if (!rt_file(path))
	{
		printf("Error\nNot a rt file!\n");
		close(fd);
		return (1);
	}
	if (getmap(fd, minirt) == 1)
	{
		close(fd);
		return (1);	
	}
	close(fd);
	return (0);
}
