/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:19:23 by pipolint          #+#    #+#             */
/*   Updated: 2023/11/12 15:14:44 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				end;

	end = ft_strlen(s);
	if (!(unsigned char)c)
		return ((char *)&s[end]);
	while (end >= 0)
	{
		if (s[end] == (unsigned char)c)
			return ((char *)&s[end]);
		end--;
	}
	return (NULL);
}
