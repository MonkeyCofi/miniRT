/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ppm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:17:23 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/08 15:28:03 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	*parse_line(char *line, char check, t_ppm *ppm)
{
	char	**strs;

	strs = ft_split(line, ' ');
	if (!strs)
		return (NULL);
	if (check == 'H')
	{
		if (ft_strncmp(strs[0], "P3", 2) == 0)
			ppm->t_ppm_type = P3;
		else if (ft_strncmp(strs[0], "P6", 2) == 0)
			ppm->t_ppm_type = P6;
		else
		{
			ft_putendl_fd("Error: Invalid PPM type", STDERR_FILENO);
			return (NULL);
		}
	}
	else if (check == 'D')
	{
		ppm->width = ft_atoi(strs[0]);
		ppm->height = ft_atoi(strs[1]);
	}
	else if (check == 'I')
		ppm->intensity = ft_atoi(strs[0]);
	return (NULL);
}

void	read_ppm_header(int fd, t_ppm *ppm)
{
	char	*line;

	line = get_next_line(fd);
	parse_line(line, 'H', ppm);
	free(line);
	line = get_next_line(fd);
	parse_line(line, 'D', ppm);
	free(line);
	line = get_next_line(fd);
	parse_line(line, 'I', ppm);
	free(line);
}

//t_tuple	fill_color(unsigned char *buff, int index)
//{
//	t_tuple	color;
	
//	color.r = buff[index * 3] / 255;
//	color.g = buff[index * 3 + 1] / 255;
//	color.b = buff[index * 3 + 2] / 255;
//	return (color);
//}

//t_tuple	**fill_ppm_buffer(t_ppm *ppm)
//{
//	int		i;
//	int		j;
//	t_tuple	**colors;

//	i = -1;
//	colors = ft_calloc(1, sizeof(t_tuple *) * (ppm->height + 1));
//	while (++i < ppm->height)
//	{
//		j = -1;
//		colors[i] = ft_calloc(1, sizeof(t_tuple) * (ppm->width + 1));
//		while (++j < ppm->width)
//		{
//			colors[i][j] = fill_color((unsigned char *)ppm->buffer, i * ppm->width + j);
//		}
//	}
//	return (colors);
//}

t_tuple	fill_color(char *buffer)
{
	t_tuple	color;

	color.r = *buffer * 3;
	color.g = *buffer * 3 + 1;
	color.b = *buffer * 3 + 2;
	color.a = 1;
	return (color);
}

t_tuple	**fill_ppm_buffer(t_ppm *ppm)
{
	int		i;
	int		j;
	char	*ptr;
	t_tuple	**colors;

	i = -1;
	colors = ft_calloc(1, sizeof(t_tuple *) * ppm->height);
	ptr = ppm->buf;
	while (++i < ppm->height)
	{
		j = -1;
		colors[i] = ft_calloc(1, sizeof(t_tuple) * ppm->width);
		while (++j < ppm->width)
		{
			/*
				values  are stored in three-byte intervals
				each byte representing a color channel; r g b
				store the values in a 2d array of tuples: 
			*/
			colors[i][j] = fill_color(ptr);
			ptr += 3;
		}
	}
	return (colors);
}

t_ppm	*create_ppm(char *filename)
{
	t_ppm	*ppm;
	FILE	*ppm_file;
	int		fd;
	ssize_t	r;

	fd = open(filename, O_RDONLY);
	ppm_file = fopen(filename, "rb");
	if (ppm_file == NULL)
		return (NULL);
	ppm = ft_calloc(1, sizeof(t_ppm));
	read_ppm_header(fd, ppm);
	ppm->buf = ft_calloc(1, sizeof(t_pixel) * (ppm->height * ppm->width * 3));
	//r = read(fd, ppm->buffer, sizeof(t_pixel) * ppm->height * ppm->width);
	r = read(fd, ppm->buf, sizeof(t_pixel) * ppm->height * ppm->width);
	if (r == -1)
	{
		write(2, "Error reading from ppm file\n", 28);
		// general free required
		return (NULL);
	}
	ppm->colors = fill_ppm_buffer(ppm);
	return (ppm);
}

//void	write_to_ppm(t_ppm *ppm)
//{
//	int	fd;

//	fd = open("new.ppm", O_CREAT | O_RDWR, 0777);
//	ft_putendl_fd("P6", fd);
//	ft_putendl_fd("1024 1024", fd);
//	ft_putendl_fd("255", fd);
//	ft_putstr_fd((char *)ppm->buffer, fd);
//}