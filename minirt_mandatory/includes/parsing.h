/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:47:27 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/10 21:05:02 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

void	parse_error(t_minirt *m, char *err, \
char **parse_arr, int print_line_num);

t_shape	*alloc_shape(t_minirt *m);
int		parse_sphere(t_minirt *minirt, char *string, int *j);
int		parse_plane(t_minirt *minirt, char *string, int *j);
int		parse_cylinder(t_minirt *minirt, char *string, int *j);
int		parse_ambient(t_minirt *minirt, char *string);
int		parse_light(t_minirt *minirt, char *string);
int		parse_camera(t_minirt *minirt, char *string);
t_bool	dovector(t_minirt *m, char *string, t_tuple *calc, t_bool should_norm);
t_bool	dovectorcolor(char *string, t_tuple *calc);
int		isulong(char *str);
int		check_ulong(char *str, double *num);
int		check_double(char *str, double *num, t_bool check_boumdary);
int		parsing(char *str, t_minirt *minirt, int *i);
int		rt_file(char *str);
char	*trimline(char *str);
int		invalidfile(t_minirt *minirt);
int		getmap(int fd, t_minirt *minirt, int i);
int		check_height(t_shape *shape, char *str, double *num);
int		check_radius(t_shape *shape, char *str, double *num);
int		fileopen(char *path, t_minirt *minirt);
int		check_magnitude(t_minirt *m, t_tuple *vector, char *line);

int		set_sphere_only(int *clones, t_bool is_sphere);

#endif