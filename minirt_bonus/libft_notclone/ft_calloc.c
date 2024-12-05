/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 22:36:00 by pipolint          #+#    #+#             */
/*   Updated: 2023/11/12 13:53:54 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;

	if (size && count > (SIZE_MAX / size))
		return (NULL);
	ret = malloc(count * size);
	if (!ret)
		return (NULL);
	ft_bzero((unsigned char *)ret, count * size);
	return (ret);
}
