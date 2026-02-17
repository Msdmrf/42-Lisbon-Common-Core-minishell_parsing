/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:44:21 by migusant          #+#    #+#             */
/*   Updated: 2025/05/26 17:25:02 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int		ft_word_count(char const *s, char c);
static int		ft_fill_words(char **words, const char *s, char c);
static void		*ft_free(char **strs, int count);
static char		*ft_word_dup(char const *s, int start, int end);

static int	ft_word_count(char const *s, char c)
{
	int	i;
	int	count;
	int	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (s[i])
	{
		if ((s[i] != c && in_word == 1) || (s[i] == c && in_word == 0))
			i++;
		else if (s[i] != c && in_word == 0)
		{
			count++;
			in_word = 1;
			i++;
		}
		else if (s[i] == c && in_word == 1)
		{
			in_word = 0;
			i++;
		}
	}
	return (count);
}

static int	ft_fill_words(char **words, const char *s, char c)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > start)
		{
			words[j] = ft_word_dup(s, start, i);
			if (!words[j])
				return (ft_free(words, j), 0);
			j++;
		}
	}
	words[j] = NULL;
	return (1);
}

static char	*ft_word_dup(char const *s, int start, int end)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = s[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

static void	*ft_free(char **strs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**words;

	if (!s)
		return (ft_calloc(sizeof(char *), 1));
	words = ft_calloc(sizeof(char *), (ft_word_count(s, c) + 1));
	if (!words)
		return (NULL);
	if (!ft_fill_words(words, s, c))
		return (NULL);
	return (words);
}
