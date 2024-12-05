/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:33:21 by pipolint          #+#    #+#             */
/*   Updated: 2023/11/07 18:37:29 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*_src;
	unsigned char	*_dst;
	size_t			i;

	if (!dst && !src)
		return (NULL);
	_dst = (unsigned char *)dst;
	_src = (unsigned char *)src;
	i = 0;
	if (dst > src)
	{
		while (len--)
			_dst[len] = _src[len];
	}
	else
	{
		while (len--)
		{
			_dst[i] = _src[i];
			i++;
		}
	}
	return (dst);
}
