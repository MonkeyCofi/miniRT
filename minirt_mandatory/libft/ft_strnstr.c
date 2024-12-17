/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:09:31 by pipolint          #+#    #+#             */
/*   Updated: 2023/11/12 13:50:33 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	n_len;

	i = 0;
	n_len = ft_strlen(needle);
	if (!n_len)
		return ((char *)haystack);
	while (*haystack != '\0' && i < len)
	{
		if (!ft_strncmp(haystack, needle, n_len) && i + (n_len - 1) < len)
			return ((char *)haystack);
		haystack++;
		i++;
	}
	return (NULL);
}
