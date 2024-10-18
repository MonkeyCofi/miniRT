/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:23:17 by ahaarij           #+#    #+#             */
/*   Updated: 2024/10/19 02:20:56 by ahaarij          ###   ########.fr       */
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
		if (!is_float(str[i]))
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

int	dovectoraarij(char *string, t_tuple *calc)
{
	char	**str;
	int		i;
	int		ret;
	
	i = -1;
	ret = 0;
	str = ft_split(string, ',');
	while (str && str[++i])
	{
		if (!is_float(str[i]))
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

int	dovectororientation(char *string, t_tuple *calc)
{
	char	**str;
	int		i;
	int		ret;
	
	i = -1;
	ret = 0;
	str = ft_split(string, ',');
	while (str && str[++i])
	{
		if (!is_float(str[i]))
			ret = 1;
	}
	if (arr_len(str) != 3)
		ret = 1;
	else if (ret == 0)
	{
		calc->x = str_to_double(str[0]);
		calc->y = str_to_double(str[1]);
		calc->z = str_to_double(str[2]);
	}
	if((calc->x > 1 || calc->x < -1) || 
		(calc->y > 1 || calc->y < -1) ||
		(calc->z > 1 || calc->z < -1))
		ret = 1;
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
		if (!is_float(str[i]))
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

int	check_ulong(char *str, float *num)
{
	if(!isulong(str))
		return (1);
	*num = ft_atoi(str);
	if(*num > 180 || *num < 0)
		return (1);
	return (0);
}

int	check_double(char *str, float *num)
{
	if(!is_float(str))
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
	while(string && string[i++])
	{
		if (i == 1 && dovector(str[i], &minirt->cam->coords))
			return (printf("Error\nIssue Lies in Camera Coordinates\n"), 1);
		if (i == 2 && dovectororientation(str[i], &minirt->cam->orientation))
			return (printf("Error\nIssue Lies in Camera Orientation\n"), 1);
		if (i == 3 && check_ulong(str[i], &minirt->cam->fov))
			return (printf("Error\nIssue Lies in Camera FOV\n"), 1);
	}
	free_arr(str);
	return (0);
}

t_shape *alloc_shape(t_shape *shape)
{
	shape = ft_calloc(1, sizeof(t_shape));
	if(!shape)
		return NULL;
	shape->coords = ft_calloc(1, sizeof(t_tuple));
	if(!shape->coords)
		return NULL;
	shape->material = ft_calloc(1, sizeof(t_mater));
	if(!shape->material)
		return NULL;
	shape->material->color = ft_calloc(1, sizeof(t_tuple));
	if(!shape->material->color)
		return NULL;
	shape->orientation = ft_calloc(1, sizeof(t_tuple));
	if(!shape->orientation)
		return (NULL);
	return (shape);
}

int	parse_sphere(t_minirt *minirt, char *string, int *j)
{
	int 	i;
	char	**str;
	float	diameter;

	str = ft_split(string, ' ');
	i = 1;
	if(arr_len(str) != 4)
		return (1);
	minirt->shapes[*j] = alloc_shape(minirt->shapes[*j]);
	while (string && string[i])
	{
		if (i == 1 && dovectoraarij(str[i], minirt->shapes[*j]->coords))
			return (printf("Error\nIssue Lies in Sphere Coordinates\n"), 1);
		if (i == 2 && check_double(str[i], &diameter))
			return (printf("Error\nIssue Lies in Sphere Diameter\n"), 1);
		if (i == 3 && dovectorcolor(str[i], minirt->shapes[*j]->material->color))
			return (printf("Error\nIssue Lies in Sphere Color\n"), 1);
		i++;
	}
	free_arr(str);
	minirt->shapes[*j]->type = SPHERE;
	minirt->shapes[*j]->r = diameter / 2;
	minirt->object_count++;
	*j += 1;
	return (0);
}

int	parse_plane(t_minirt *minirt, char *string, int *j)
{
	int 	i;
	char	**str;

	str = ft_split(string, ' ');
	i = 1;
	if(arr_len(str) != 4)
		return (1);
	minirt->shapes[*j] = alloc_shape(minirt->shapes[*j]);
	while (string && string[i])
	{
		if (i == 1 && dovectoraarij(str[i], minirt->shapes[*j]->coords))
			return (printf("Error\nIssue Lies in Plane Coordinates\n"), 1);
		if (i == 2 && dovectororientation(str[i], minirt->shapes[*j]->orientation))
			return (printf("Error\nIssue Lies in Plane Orientation\n"), 1);
		if (i == 3 && dovectorcolor(str[i], minirt->shapes[*j]->material->color))
			return (printf("Error\nIssue Lies in Plane Color\n"), 1);
		i++;
	}
	free_arr(str);
	minirt->shapes[*j]->type = PLANE;
	minirt->object_count += 1;
	*j += 1;
	return (0);
}

int	parse_cylinder(t_minirt *minirt, char *string, int *j)
{
	int 	i;
	char	**str;
	float	diameter = 0.0;
	float	height;

	str = ft_split(string, ' ');
	i = 1;
	if(arr_len(str) != 6)
		return (1);
	minirt->shapes[*j] = alloc_shape(minirt->shapes[*j]);
	while (string && string[i])
	{
		if (i == 1 && dovectoraarij(str[i], minirt->shapes[*j]->coords))
			return (printf("Error\nIssue Lies in Cylinder Coordinates\n"), 1);
		if (i == 2 && dovectororientation(str[i], minirt->shapes[*j]->orientation))
			return (printf("Error\nIssue Lies in Cylinder Orientation\n"), 1);
		if (i == 3 && check_double(str[i], &diameter))
			return(printf("Error\nIssue Lies in Cylinder Diameter\n"), 1);
		if (i == 4 && check_double(str[i], &height))
			return(printf("Error\nIssue Lies in Cylinder Height\n"), 1);
		if (i == 5 && dovectorcolor(str[i], minirt->shapes[*j]->material->color))
			return (printf("Error\nIssue Lies in Cylinder Color\n"), 1);
		i++;
	}
	free_arr(str);
	minirt->shapes[*j]->type = CYLINDER;
	minirt->shapes[*j]->r = diameter / 2;
	minirt->object_count += 1;
	*j += 1;
	return (0);
}

int parse_ambient(t_minirt *minirt, char *string)
{
	int i;
	char **str;
	if(minirt->ambient->flag != 0)
		return (1);
	else
		minirt->ambient->flag = 1;
	str = ft_split(string, ' ');
	i = 1;
	if(arr_len(str) != 3)
		return (1);
	minirt->ambient = ft_calloc(1, sizeof(t_ambient));
	minirt->ambient->color = ft_calloc(1, sizeof(t_tuple));
	while(string && string[i])
	{
		if(i == 1 && check_double(str[i], &minirt->ambient->ratio))
			return(printf("Error\nIssue Lies in Ambient Ratio\n"), 1);
		if(i == 2 && dovectorcolor(str[i], minirt->ambient->color))
			return(printf("Error\nIssue Lies in Ambient Color\n"), 1);
		i++;
	}
	free_arr(str);
	return (0);
}

int	parse_light(t_minirt *minirt, char *string, int *j)
{
	int i;
	char **str;
	str = ft_split(string, ' ');
	i = 1;
	if(arr_len(str) != 4)
		return (1);
	minirt->lights[*j] = ft_calloc(1, sizeof(t_ambient));
	minirt->lights[*j]->position = ft_calloc(1, sizeof(t_tuple));
	minirt->lights[*j]->intensity = ft_calloc(1, sizeof(t_tuple));
	while(string && string[i])
	{
		if(i == 1 && dovectoraarij(str[i], minirt->lights[*j]->position))
			return(printf("Error\nIssue Lies in Light Coords"), 1);
		if(i == 2 && check_double(str[i], &minirt->lights[*j]->brightness))
			return(printf("Error\nIssue Lies in Light Brightness"), 1);
		if(i == 3 && dovectorcolor(str[i], minirt->lights[*j]->intensity))
			return(printf("Error\nIssue Lies in Light Color"), 1);
		i++;
	}
	free_arr(str);
	minirt->light_count++;
	return (0);
}

int	parsing(char *str, t_minirt *minirt, int *i, int *j)
{
	if(strncmp(str, "#", 1) == 0)
		return (0);
	if (strncmp(str, "sp", 2) == 0)
		return (parse_sphere(minirt, str, i));
	if (strncmp(str, "cy", 2) == 0)
		return (parse_cylinder(minirt, str, i));
	if (strncmp(str, "pl", 2) == 0)
		return (parse_plane(minirt, str, i));
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
			ret = 1;
		free(line);
	}
	close(fd);
	if (!ret && (invalidfile(minirt) == 1))
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