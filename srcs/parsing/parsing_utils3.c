/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:35:15 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/04 10:51:02 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	write_two_errs(t_minirt *m, char *str1, int need_newline, char *str2, \
	int need_newline_end)
{
	if (str1 && write(2, str1, ft_strlen(str1)) == -1)
		free_minirt(m);
	if (need_newline)
	{
		if (write(2, "\n", 1) == -1)
			free_minirt(m);
	}
	if (str2 && write(2, str2, ft_strlen(str2)) == -1)
		free_minirt(m);
	if (need_newline_end)
	{
		if (write(2, "\n", 1) == -1)
			free_minirt(m);
	}
}

t_bool	open_image(t_minirt *m, t_mater *material, char *filename)
{
	t_img	*img;

	img = material->texture;
	img->img = mlx_xpm_file_to_image(m->mlx->mlx, filename, &img->img_width, \
		&img->img_height);
	if (!img->img)
	{
		write_err("Error: Img: ", 0);
		write_err(IMG_ERR, 0);
		write_err("Error string: ", 0);
		return (error);
	}
	img->img_addr = mlx_get_data_addr(img->img, &img->bpp, \
		&img->line_length, &img->endian);
	if (!img->img_addr)
	{
		write_err("Error: Image: Could not fetch texture data", '\n');
		write_err("Error string: ", 0);
		return (error);
	}
	return (true);
}

void	parse_error(t_minirt *m, char *err, char *line, char **parse_arr)
{
	char	*line_no;

	line_no = NULL;
	line_no = ft_itoa(m->line);
	if (!line_no)
	{
		write(2, "Error: Cannot allocate memory for string\n", 41);
		free_arr(parse_arr);
		free_minirt(m);
	}
	write_two_errs(m, err, 1, "Line number: ", 0);
	write(2, line_no, ft_strlen(line_no));
	write(2, "\n", 1);
	write(2, "Line: ", 6);
	if (line)
		write_err(line, '\n');
	if (line_no)
		free(line_no);
	free_arr(parse_arr);
	free_minirt(m);
}

int	check_radius(t_shape *shape, char *str, double *num)
{
	double	res;

	if (!is_double(str))
		return (1);
	if (!num)
	{
		res = str_to_double(str);
		if (res / 2 < 0 || res < 0)
			return (1);	
		shape->r = res / 2;
		printf("shape radius is %f\n", shape->r);
		return (0);
	}
	*num = str_to_double(str);
	printf("shape radius is %f\n", shape->r);
	if (*num / 2 < 0 || *num < 0)
		return (1);
	shape->r = (*num) / 2;
	return (0);
}

char	*trimline(char *str)
{
	int		i;
	char	*temp;

	i = -1;
	temp = str;
	while (temp && temp[++i])
	{
		if (temp[i] == '\t' || temp[i] == '\n')
			temp[i] = ' ';
	}
	str = ft_strtrim(temp, " ");
	free(temp);
	return (str);
}
