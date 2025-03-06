/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:52:08 by pipolint          #+#    #+#             */
/*   Updated: 2023/12/21 14:54:47 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	move_buffer(char *buffer)
{
	if (ft_strchr(buffer, '\n'))
		ft_memmove(buffer, (ft_strchr(buffer, '\n') + 1),
			ft_strlen(ft_strchr(buffer, '\n') + 1) + 1);
	else
		buffer[0] = 0;
}

static char	*join_buf(char *result, char *buffer)
{
	char	*line;

	if (!result)
	{
		result = ft_calloc(1, sizeof(char));
		if (!result)
			return (NULL);
	}
	line = ft_newlinejoin(result, buffer);
	if (!line)
	{
		free(result);
		return (NULL);
	}
	free(result);
	move_buffer(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[OPEN_MAX][BUFFER_SIZE + 1u];
	char		*ret;
	ssize_t		bytes;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE > 2147483647 || BUFFER_SIZE <= 0)
		return (NULL);
	ret = NULL;
	while (!ret || !ft_strchr(ret, '\n'))
	{
		if (!*buffer[fd])
		{
			bytes = read(fd, buffer[fd], BUFFER_SIZE);
			if (bytes == 0)
				return (ret);
			if (bytes < 0 && ret)
				free(ret);
			if (bytes < 0)
				return (NULL);
			buffer[fd][bytes] = '\0';
		}
		ret = join_buf(ret, buffer[fd]);
		if (!ret)
			return (NULL);
	}
	return (ret);
}
