/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:42:43 by pipolint          #+#    #+#             */
/*   Updated: 2023/11/10 19:30:29 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_end;
	size_t	dst_len;
	size_t	i;

	if (!dst && dstsize == 0)
		return (ft_strlen(src));
	dst_len = ft_strlen(dst);
	dst_end = dst_len;
	if (!dstsize || dst_len >= dstsize)
		return (ft_strlen(src) + dstsize);
	i = 0;
	while (src[i] && i < dstsize - dst_end - 1)
	{
		dst[dst_end + i] = src[i];
		i++;
	}
	dst[dst_end + i] = '\0';
	return (dst_len + ft_strlen(src));
}
