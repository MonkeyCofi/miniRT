/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:47:27 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/09 16:41:32 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

//void	parse_error(t_minirt *m, char *err, char *line, char **parse_arr);
void	parse_error(t_minirt *m, char *err, char **parse_arr, int print_line_num);
void	write_two_errs(t_minirt *m, char *str1, int need_newline, char *str2);
t_bool	open_image(t_minirt *m, t_mater *material, char *filename);
t_bool	open_texture(t_minirt *m, t_mater *material, char **params);

t_shape	*alloc_shape(t_minirt *m);
int		parse_sphere(t_minirt *minirt, char *string, int *j);
int		parse_plane(t_minirt *minirt, char *string, int *j);
int		parse_cylinder(t_minirt *minirt, char *string, int *j);
int		parse_cone(t_minirt *minirt, char *string, int *j);
int		parse_ambient(t_minirt *minirt, char *string);
int		parse_light(t_minirt *minirt, char *string, int *j);
int		parse_camera(t_minirt *minirt, char *string);
t_bool	dovector(char *string, t_tuple *calc, t_bool should_norm);
t_bool	dovectorcolor(char *string, t_tuple *calc);
int		isulong(char *str);
int		check_ulong(char *str, double *num);
int		check_double(char *str, double *num, t_bool check_boumdary);
int		parsing(char *str, t_minirt *minirt, int *i, int *j);
int		rt_file(char *str);
char	*trimline(char *str);
int		invalidfile(t_minirt *minirt);
int		getmap(int fd, t_minirt *minirt, int i, int j);
int		check_height(t_shape *shape, char *str, double *num);
int		check_radius(t_shape *shape, char *str, double *num);
int		fileopen(char *path, t_minirt *minirt);

int		recognizepattern(t_minirt *m, char *string, \
						t_mater *material, int *clones);

int		recognizeambient(t_minirt *m, char *string, \
						t_mater *material, int *clones);

int		recognizediffuse(t_minirt *m, char *string, \
						t_mater *material, int *clones);

int		recognizespecular(t_minirt *m, char *string, \
						t_mater *material, int *clones);

int		recognizetexture(t_minirt *m, char *string, \
						t_mater *material, int *clones);
						
int		set_sphere_only(int *clones, t_bool is_sphere);

#endif