/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:22:05 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/04 19:55:30 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	fileopen(char *path, t_minirt *minirt)
{
	int	fd;
	int	i;
	int	j;

	i = 0;
	j = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nFailed to open file!\n");
		return (close(fd), 1);
	}
	if (!rt_file(path))
	{
		printf("Error\nNot a rt file!\n");
		return (close(fd), 1);
	}
	if (getmap(fd, minirt, i, j) == 1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static void	test_file(t_minirt *m, char *filename)
{
	int	file_fd;

	file_fd = open(filename, O_RDONLY);
	if (file_fd == -1)
		parse_error(m, "Error: Failed to open texture file", NULL, NULL);
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
