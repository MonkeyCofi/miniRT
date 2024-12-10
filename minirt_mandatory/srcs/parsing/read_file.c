/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:22:05 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/10 15:24:22 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	fileopen(char *path, t_minirt *minirt)
{
	int	i;

	i = 0;
	minirt->file_fd = open(path, O_RDONLY);
	if (minirt->file_fd == -1)
	{
		write_check(minirt, "Error\nCouldn't open rt file\n");
		return (1);
	}
	if (!rt_file(path))
	{
		write_check(minirt, "Error\nIncorrect file format\n");
		return (close(minirt->file_fd), 1);
	}
	if (getmap(minirt->file_fd, minirt, i) == 1)
	{
		close(minirt->file_fd);
		return (1);
	}
	close(minirt->file_fd);
	return (0);
}
