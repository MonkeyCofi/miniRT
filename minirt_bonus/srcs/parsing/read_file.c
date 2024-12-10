/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:22:05 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/10 15:56:22 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	fileopen(char *path, t_minirt *minirt)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	minirt->file_fd = open(path, O_RDONLY);
	if (minirt->file_fd == -1)
	{
		close(minirt->file_fd);
		parse_error(minirt, "Error\nCouldn't open rt file", NULL, 0);
	}
	if (!rt_file(path))
	{
		close(minirt->file_fd);
		parse_error(minirt, "Error\nInvalid rt file", NULL, 0);
	}
	getmap(minirt->file_fd, minirt, i, j);
	if (minirt->file_fd != -1)
		close(minirt->file_fd);
	return (0);
}

static void	test_file(t_minirt *m, char *filename)
{
	int	file_fd;

	file_fd = open(filename, O_RDONLY);
	if (file_fd == -1)
		parse_error(m, "Failed to open texture file", NULL, 1);
	close(file_fd);
}

t_bool	open_image(t_minirt *m, t_mater *material, char *filename)
{
	t_img	*img;

	test_file(m, filename);
	img = material->texture;
	img->img = mlx_xpm_file_to_image(m->mlx->mlx, filename, &img->img_width, \
		&img->img_height);
	if (!img->img)
	{
		write_check(m, "Error\nFailed to convert xpm to image\n");
		return (error);
	}
	img->img_addr = mlx_get_data_addr(img->img, &img->bpp, \
		&img->line_length, &img->endian);
	if (!img->img_addr)
	{
		write_check(m, "Error\nFailed to fetch image data");
		return (error);
	}
	return (true);
}
