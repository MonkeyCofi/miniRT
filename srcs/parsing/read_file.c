/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:22:05 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/04 14:49:42 by ahaarij          ###   ########.fr       */
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
