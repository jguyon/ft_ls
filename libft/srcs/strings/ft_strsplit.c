/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 17:06:07 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/02 01:33:09 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/ft_memory.h"
#include "libft/ft_strings.h"

static char	const	*next_word(char const *str, char c, size_t *word_len)
{
	*word_len = 0;
	while (*str && *str != c)
	{
		++(*word_len);
		++str;
	}
	while (*str && *str == c)
		++str;
	return (*str ? str : NULL);
}

static size_t		count_words(char const *str, char c)
{
	size_t	len;
	size_t	word_len;

	len = 0;
	while (str && ((str = next_word(str, c, &word_len)) || word_len))
	{
		if (word_len)
			++len;
	}
	return (len);
}

static size_t		insert_words(char const *str, char c, char **words)
{
	char const	*next;
	size_t		word_len;
	size_t		i;

	next = str;
	i = 0;
	while (next && ((next = next_word(next, c, &word_len)) || word_len))
	{
		if (word_len)
		{
			if ((words[i] = ft_strsub(str, 0, word_len)))
				++i;
		}
		str = next;
	}
	return (i);
}

char				**ft_strsplit(char const *str, char c)
{
	size_t	len;
	char	**words;
	size_t	i;

	len = count_words(str, c);
	if (!(words = (char **)ft_memalloc(sizeof(*words) * (len + 1))))
		return (NULL);
	if (insert_words(str, c, words) != len)
	{
		i = 0;
		while (i < len)
		{
			if (words[i])
				free(words[i]);
			++i;
		}
		free(words);
	}
	return (words);
}
