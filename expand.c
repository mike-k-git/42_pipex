/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 20:56:55 by mkugan            #+#    #+#             */
/*   Updated: 2025/06/18 21:22:44 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_wc(char const *s, char c)
{
	size_t	wc;
	char	quote_char;

	wc = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			quote_char = 0;
			if ((*s == '\'' || *s == '"') && quote_char == 0)
				quote_char = *(s)++;
			wc++;
			while (*s && (*s != c || quote_char))
			{
				if (*s == quote_char)
					quote_char = 0;
				else if ((*s == '\'' || *s == '"') && quote_char == 0)
					quote_char = *s;
				s++;
			}
		}
	}
	return (wc);
}

static size_t	ft_free_expand_array(char **arr, size_t i)
{
	while (i-- > 0)
		free(arr[i]);
	free(arr);
	return (0);
}

static char	*ft_strip_quotes(const char *s, size_t len)
{
	if (len >= 2
		&& ((s[0] == '\'' && s[len - 1] == '\'')
			|| (s[0] == '"' && s[len - 1] == '"')))
		return (ft_substr(s + 1, 0, len - 2));
	return (ft_substr(s, 0, len));
}

static	size_t	ft_elalloc(char **arr, size_t i, const char *s, char c)
{
	size_t	word_len;
	char	quote_char;

	quote_char = 0;
	word_len = 0;
	while (s[word_len] && (s[word_len] != c || quote_char))
	{
		if (s[word_len] == '\'' || s[word_len] == '"')
		{
			if (quote_char == 0)
				quote_char = s[word_len];
			else if (s[word_len] == quote_char)
				quote_char = 0;
		}
		word_len++;
	}
	arr[i] = ft_strip_quotes(s, word_len);
	if (!arr[i])
		return (ft_free_expand_array(arr, i));
	return (word_len);
}

char	**ft_expand(char *s, char c)
{
	char	**arr;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	arr = (char **)malloc(sizeof(char *) * (ft_wc(s, c) + 1));
	if (!arr)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			s += ft_elalloc(arr, i, s, c);
			if (!arr)
				return (NULL);
			i++;
		}
	}
	arr[i] = NULL;
	return (arr);
}
