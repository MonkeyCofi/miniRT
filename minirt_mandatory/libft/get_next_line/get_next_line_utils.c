/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:33:00 by pipolint          #+#    #+#             */
/*   Updated: 2023/12/21 15:01:49 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_newlinejoin(char *result, char *buffer)
{
	char	*new;
	size_t	i;
	int		j;

	i = 0;
	j = -1;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] && buffer[i] == '\n')
		i++;
	new = malloc((sizeof(char) * ft_strlen(result) + i) + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (result[++j])
		new[j] = result[j];
	while (buffer[i] && buffer[i] != '\n')
		new[j++] = buffer[i++];
	if (buffer[i] && buffer[i] == '\n')
		new[j++] = buffer[i++];
	new[j] = '\0';
	return (new);
}
