/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:31:10 by pipolint          #+#    #+#             */
/*   Updated: 2023/11/12 13:48:48 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*p_src;
	unsigned char	*p_dest;

	if (!dst && !src)
		return (NULL);
	i = 0;
	p_src = (unsigned char *)src;
	p_dest = (unsigned char *)dst;
	while (i < n)
	{
		p_dest[i] = p_src[i];
		i++;
	}
	return (p_dest);
}
