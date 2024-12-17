/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:38:30 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/10 21:09:45 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char *set, int c)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static int	get_malloc_size(char *s, char *set)
{
	int		i;
	int		end;
	int		mal_size;

	i = 0;
	end = ft_strlen(s);
	while (s[i] && is_set(set, s[i]))
		i++;
	if (i == end)
		return (0);
	while (is_set(set, s[end - 1]))
		end--;
	mal_size = end - i;
	if (mal_size < 0)
		return (0);
	return (mal_size);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		mal_size;
	char	*new_str;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	mal_size = get_malloc_size((char *)s1, (char *)set);
	if (mal_size == 0)
		return (ft_strdup(""));
	new_str = malloc(sizeof(char) * (mal_size + 1));
	if (!new_str)
		return (NULL);
	while (is_set((char *)set, s1[i]) && s1[i])
		i++;
	ft_strlcpy(new_str, (char *)&s1[i], mal_size + 1);
	return (new_str);
}
