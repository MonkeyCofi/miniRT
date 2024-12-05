/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:22:05 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/05 20:03:30 by pipolint         ###   ########.fr       */
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
		write_check(minirt, "Error\nCouldn't open rt file\n");
		return (close(fd), 1);
	}
	if (!rt_file(path))
	{
		write_check(minirt, "Error\nIncorrect file format\n");
		return (close(fd), 1);
	}
	if (getmap(fd, minirt, i) == 1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
