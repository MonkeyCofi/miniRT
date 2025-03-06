/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:52:28 by pipolint          #+#    #+#             */
/*   Updated: 2023/11/12 13:51:29 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	words;
	int	letters;
	int	i;

	i = 0;
	words = 0;
	letters = 0;
	while (s[i])
	{
		if (s[i] != c)
			letters++;
		else if (s[i] == c && letters)
		{
			letters = 0;
			words++;
		}
		if (s[i + 1] == '\0' && s[i] != c)
			words++;
		i++;
	}
	return (words);
}

static int	get_length(const char *s, char c)
{
	int	length;

	length = 0;
	while (*s != '\0' && *s != c)
	{
		length++;
		s++;
	}
	return (length);
}

static void	add_words(char **words, char *s, char c)
{
	char	*word;
	int		current_word;
	int		i;

	current_word = 0;
	while (*s)
	{
		i = 0;
		if (*s != c)
		{
			word = (char *)malloc(sizeof(char) * (get_length(s, c) + 1));
			if (!word)
				return ;
			while (*s != c && *s)
				word[i++] = *s++;
			word[i] = '\0';
			words[current_word++] = ft_strdup(word);
			free(word);
		}
		else
			s++;
	}
	words[current_word] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	int		word_count;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	words = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!words)
		return (NULL);
	add_words(words, (char *)s, c);
	return (words);
}
