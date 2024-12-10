/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:17:00 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/10 16:06:25 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	**ft_split_and_check(t_minirt *m, char *str, char delim, \
	t_bool should_exit)
{
	char	**arr;

	arr = ft_split(str, delim);
	if (arr == NULL)
	{
		if (should_exit)
			parse_error(m, "Error\nft_split: couldn't split string", \
				NULL, 1);
		else
		{
			write_check(m, "Error\nft_spit: Couldn't split string\n");
			return (NULL);
		}
	}
	return (arr);
}

void	init_mlx(t_minirt *m)
{
	m->mlx = calloc_and_check(sizeof(t_mlx), 1, m, MLX_ERR);
	m->mlx->mlx = mlx_init();
	if (!m->mlx->mlx)
	{
		parse_error(m, "Couldn't initialize mlx", NULL, 0);
	}
	m->mlx->win = mlx_new_window(m->mlx->mlx, WIDTH, HEIGHT, "miniRT");
	if (!m->mlx->win)
		free_minirt(m, 1);
	m->mlx->img.img = mlx_new_image(m->mlx->mlx, WIDTH, HEIGHT);
	if (!(m->mlx->img.img))
		free_minirt(m, 1);
	m->mlx->img.img_addr = mlx_get_data_addr(m->mlx->img.img, &m->mlx->img.bpp, \
	&m->mlx->img.line_length, &m->mlx->img.endian);
	m->mlx->img.img_height = HEIGHT;
	m->mlx->img.img_width = WIDTH;
}

static int	count_shapes(t_minirt *m, char *file)
{
	int		fd;
	char	*line;
	int		shapes;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		write_check(NULL, "Error\nCouldn't open rt file\n");
		free_minirt(m, EXIT_FAILURE);
	}
	shapes = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!ft_strncmp(line, "\n", 1))
		{
			free(line);
			continue ;
		}
		line = trimline(line);
		if (!ft_strncmp(line, "#", 1))
		{
			free(line);
			continue ;
		}
		if (!ft_strncmp(line, "cy", 2) || !ft_strncmp(line, "co", 2) || !ft_strncmp(line, "sp", 2)
			|| !ft_strncmp(line, "pl", 2))
			shapes++;
		free(line);
	}
	close(fd);
	return (shapes);
}

t_minirt	*init_minirt(char *file)
{
	t_minirt	*m;

	m = calloc_and_check(sizeof(t_minirt), 1, NULL, MRT_ERR);
	m->cam = calloc_and_check(sizeof(t_camera), 1, m, CAM_ERR);
	m->cam->trans = return_point(0, 0, 0);
	m->shapes = calloc_and_check(sizeof(t_shape *), \
	count_shapes(m, file), m, SHP_ERR);
	m->ambient = calloc_and_check(sizeof(t_ambient), 1, m, AMB_ERR);
	m->light = calloc_and_check(sizeof(t_light), 1, m, LGT_ERR);
	m->up = return_tuple(0, 1, 0, VECTOR);
	minirt->line = 0;
	m->ambient->flag = 0;
	m->ambient->ratio = 0;
	m->cam->flag = 0;
	m->object_count = 0;
	m->file_fd = -1;
	return (m);
}
