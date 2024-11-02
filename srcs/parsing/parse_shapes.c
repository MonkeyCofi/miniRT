/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:45:40 by ahaarij           #+#    #+#             */
/*   Updated: 2024/11/03 00:45:29 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape *alloc_shape(t_shape *shape)
{
	shape = ft_calloc(1, sizeof(t_shape));
	if(!shape)
		return NULL;
	// shape->coords = ft_calloc(1, sizeof(t_tuple));
	// if(!shape->coords)
	// 	return NULL;
	shape->material = create_default_material();
	if(!shape->material)
		return (NULL);
	// shape->material->color = ft_calloc(1, sizeof(t_tuple));
	// if(!shape->material->color)
	// 	return NULL;
	// shape->material->pattern = ft_calloc(1, sizeof(t_pattern));
	// if(!shape->material->pattern)
	// 	return NULL;
	// shape->material->pattern->color_two = ft_calloc(1, sizeof(t_tuple));
	// if(!shape->material->pattern->color_two)
	// 	return NULL;
	// shape->material->pattern->color_one = ft_calloc(1, sizeof(t_tuple));
	// if(!shape->material->pattern->color_one)
	// 	return NULL;	
	// shape->orientation = ft_calloc(1, sizeof(t_tuple));
	// if(!shape->orientation)
	// 	return (NULL);
	return (shape);
}

int	parse_sphere(t_minirt *minirt, char *string, int *j)
{
	int 	i;
	char	**str;
	double	diameter;

	str = ft_split(string, ' ');
	i = 1;
	if(arr_len(str) != 4 && arr_len(str) != 5)
	{
		return (1);
	}
	minirt->shapes[*j] = alloc_shape(minirt->shapes[*j]);
	while (str && str[i])
	{
		if (i == 1 && dovector(str[i], &minirt->shapes[*j]->coords))
			return (printf("Error\nIssue Lies in Sphere Coordinates\n"), 1);
		if (i == 2 && check_double(str[i], &diameter))
			return (printf("Error\nIssue Lies in Sphere Diameter\n"), 1);
		if (i == 3 && dovectorcolor(str[i], &minirt->shapes[*j]->material->color))
			return (printf("Error\nIssue Lies in Sphere Color\n"), 1);
		if (i == 4 && recognizepattern(str[i], minirt->shapes[*j]->material))
			return (printf("Error\nIssue Lies in Pattern\n"), 1);
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
	if(arr_len(str) != 4 && arr_len(str) != 5)
		return (1);
	minirt->shapes[*j] = alloc_shape(minirt->shapes[*j]);
	while (str && str[i])
	{
		if (i == 1 && dovector(str[i], &minirt->shapes[*j]->coords))
			return (printf("Error\nIssue Lies in Plane Coordinates\n"), 1);
		if (i == 2 && dovectororientation(str[i], &minirt->shapes[*j]->orientation))
			return (printf("Error\nIssue Lies in Plane Orientation\n"), 1);
		if (i == 3 && dovectorcolor(str[i], &minirt->shapes[*j]->material->color))
			return (printf("Error\nIssue Lies in Plane Color\n"), 1);
		if (i == 4 && recognizepattern(str[i], minirt->shapes[*j]->material))
			return (printf("Error\nIssue Lies in Pattern\n"), 1);
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
	double	diameter = 0.0;
	double	height = 0.0;
	str = ft_split(string, ' ');
	// printf("%s\n", string);
	i = 1;
	if(arr_len(str) != 6 && arr_len(str) != 7)
		return (1);
	minirt->shapes[*j] = alloc_shape(minirt->shapes[*j]);
	while (str && str[i])
	{
		if (i == 1 && dovector(str[i], &minirt->shapes[*j]->coords))
			return (printf("Error\nIssue Lies in Cylinder Coordinates\n"), 1);
		if (i == 2 && dovectororientation(str[i], &minirt->shapes[*j]->orientation))
			return (printf("Error\nIssue Lies in Cylinder Orientation\n"), 1);
		if (i == 3 && check_double(str[i], &diameter))
			return(printf("Error\nIssue Lies in Cylinder Diameter\n"), 1);
		if (i == 4 && check_double(str[i], &height))
			return(printf("Error\nIssue Lies in Cylinder Height\n"), 1);
		if (i == 5 && dovectorcolor(str[i], &minirt->shapes[*j]->material->color))
			return (printf("Error\nIssue Lies in Cylinder Color\n"), 1);
		if (i == 6 && recognizepattern(str[i], minirt->shapes[*j]->material))
			return (printf("Error\nIssue Lies in Pattern\n"), 1);
		i++;
	}
	free_arr(str);
	minirt->shapes[*j]->type = CYLINDER;
	minirt->shapes[*j]->h = height;
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
	while(string && string[i])
	{
		if(i == 1 && check_double(str[i], &minirt->ambient->ratio))
			return(printf("Error\nIssue Lies in Ambient Ratio\n"), 1);
		if(i == 2 && dovectorcolor(str[i], &minirt->ambient->color))
			return(printf("Error\nIssue Lies in Ambient Color\n"), 1);
		i++;
	}
	free_arr(str);
	return (0);
}

int	parse_cone(t_minirt *minirt, char *string, int *j)
{
	int 	i;
	char	**str;
	double	height = 0.0;
	str = ft_split(string, ' ');
	i = 1;
	if(arr_len(str) != 5 && arr_len(str) != 6)
		return (1);
	minirt->shapes[*j] = alloc_shape(minirt->shapes[*j]);
	while (str && str[i])
	{
		if (i == 1 && dovector(str[i], &minirt->shapes[*j]->coords))
			return (printf("Error\nIssue Lies in Cone Coordinates\n"), 1);
		if (i == 2 && dovectororientation(str[i], &minirt->shapes[*j]->orientation))
			return (printf("Error\nIssue Lies in Cone Orientation\n"), 1);
		if (i == 3 && check_double(str[i], &height))
			return(printf("Error\nIssue Lies in Cone Height\n"), 1);
		if (i == 4 && dovectorcolor(str[i], &minirt->shapes[*j]->material->color))
			return (printf("Error\nIssue Lies in Cone Color\n"), 1);
		if (i == 5 && recognizepattern(str[i], minirt->shapes[*j]->material))
			return (printf("Error\nIssue Lies in Pattern\n"), 1);
		i++;
	}
	free_arr(str);
	minirt->shapes[*j]->type = CONE;
	minirt->shapes[*j]->h = height;
	minirt->object_count += 1;
	*j += 1;
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
	minirt->lights[*j] = ft_calloc(1, sizeof(t_light));
	while(str && str[i])
	{
		if(i == 1 && dovector(str[i], &minirt->lights[*j]->position))
			return(printf("Error\nIssue Lies in Light Coords"), 1);
		if(i == 2 && check_double(str[i], &minirt->lights[*j]->brightness))
			return(printf("Error\nIssue Lies in Light Brightness"), 1);
		if(i == 3 && dovectorcolor(str[i], &minirt->lights[*j]->intensity))
			return(printf("Error\nIssue Lies in Light Color"), 1);
		i++;
	}
	free_arr(str);
	minirt->light_count++;
	*j += 1;
	return (0);
}
