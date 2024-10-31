/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:47:27 by ahaarij           #+#    #+#             */
/*   Updated: 2024/10/31 08:50:27 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// #include "structs.h"

t_shape	*alloc_shape(t_shape *shape);
int		parse_sphere(t_minirt *minirt, char *string, int *j);
int		parse_plane(t_minirt *minirt, char *string, int *j);
int		parse_cylinder(t_minirt *minirt, char *string, int *j);
int		parse_cone(t_minirt *minirt, char *string, int *j);
int		parse_ambient(t_minirt *minirt, char *string);
int		parse_light(t_minirt *minirt, char *string, int *j);
int		dovector(char *string, t_tuple *calc);
int		dovectoraarij(char *string, t_tuple *calc);
int		dovectororientation(char *string, t_tuple *calc);
int		dovectorcolor(char *string, t_tuple *calc);
int		isulong(char *str);
int		check_ulong(char *str, double *num);
int		check_double(char *str, double *num);
int		parse_camera(t_minirt *minirt, char *string);
int		parsing(char *str, t_minirt *minirt, int *i, int *j);
int		rt_file(char *str);
char	*trimline(char *str);
int		invalidfile(t_minirt *minirt);
int		getmap(int fd, t_minirt *minirt);
int		fileopen(char *path, t_minirt *minirt);
int		recognizepattern(char *string, t_mater *material);

#endif