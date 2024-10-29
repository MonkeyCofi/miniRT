/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ppm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:17:23 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/29 21:40:49 by pipolint         ###   ########.fr       */
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
		{
			ppm->t_ppm_type = P6;
		}
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

t_tuple	fill_color(unsigned char *buff, int index)
{
	t_tuple	color;
	
	color.r = buff[index * 3];
	color.g = buff[index * 3 + 1];
	color.g = buff[index * 3 + 2];
	return (color);
}

t_tuple	**fill_ppm_buffer(t_ppm *ppm)
{
	int		i;
	int		j;
	t_tuple	**colors;

	i = -1;
	colors = ft_calloc(1, sizeof(t_tuple *) * (ppm->height + 1));
	while (++i < ppm->height)
	{
		j = -1;
		colors[i] = ft_calloc(1, sizeof(t_tuple) * (ppm->width + 1));
		while (++j < ppm->width)
		{
			colors[i][j] = fill_color((unsigned char *)ppm->buffer, i * ppm->width + j);
		}
	}
	return (colors);
}

t_ppm	*create_ppm(char *filename)
{
	t_ppm	*ppm;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	ppm = ft_calloc(1, sizeof(t_ppm));
	read_ppm_header(fd, ppm);
	ppm->buffer = ft_calloc(1, sizeof(t_pixel) * (ppm->height * ppm->width * 3));
	ssize_t	r = read(fd, ppm->buffer, sizeof(t_pixel) * ppm->height * ppm->width);
	(void)r;
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