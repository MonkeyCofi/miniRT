/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:42:16 by pipolint          #+#    #+#             */
/*   Updated: 2023/11/06 19:53:23 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*n;
	size_t			i;

	n = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		n[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
