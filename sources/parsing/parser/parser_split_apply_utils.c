/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split_apply_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 21:50:54 by migusant          #+#    #+#             */
/*   Updated: 2026/02/19 18:56:33 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static int	handle_quote_in_count(char c, int *in_quote, char *quote_type,
	int *in_word)
{
	int	count_increment;

	count_increment = 0;
	if (!*in_quote && (c == '"' || c == '\''))
	{
		*quote_type = c;
		*in_quote = 1;
		if (!*in_word)
		{
			*in_word = 1;
			count_increment = 1;
		}
	}
	else if (*in_quote && c == *quote_type)
		*in_quote = 0;
	return (count_increment);
}

static int	count_words_quote_aware(char *str)
{
	int		count;
	int		i;
	int		in_word;
	int		in_quote;
	char	quote_type;

	count = 0;
	i = 0;
	in_word = 0;
	in_quote = 0;
	quote_type = 0;
	while (str[i])
	{
		count += handle_quote_in_count(str[i], &in_quote, &quote_type,
				&in_word);
		if (!in_quote && is_whitespace(str[i]))
			in_word = 0;
		else if (!in_quote && !in_word && str[i] != '"' && str[i] != '\'')
		{
			in_word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static char	*extract_word_quote_aware(char *str, int *pos)
{
	int		start;
	int		in_quote;
	char	quote_type;

	start = *pos;
	in_quote = 0;
	while (str[*pos])
	{
		if (!in_quote && (str[*pos] == '"' || str[*pos] == '\''))
		{
			quote_type = str[*pos];
			in_quote = 1;
			(*pos)++;
		}
		else if (in_quote && str[*pos] == quote_type)
		{
			in_quote = 0;
			(*pos)++;
		}
		else if (!in_quote && is_whitespace(str[*pos]))
			break ;
		else
			(*pos)++;
	}
	return (ft_substr(str, start, *pos - start));
}

static int	extract_next_word(char *str, char **result, int *pos, int *i)
{
	while (str[*pos] && is_whitespace(str[*pos]))
		(*pos)++;
	if (str[*pos])
	{
		result[*i] = extract_word_quote_aware(str, pos);
		if (!result[*i])
			return (0);
		(*i)++;
	}
	return (1);
}

char	**split_quote_aware(char *str)
{
	char	**result;
	int		word_count;
	int		i;
	int		pos;

	if (!str)
		return (NULL);
	word_count = count_words_quote_aware(str);
	result = malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	pos = 0;
	while (str[pos])
	{
		if (!extract_next_word(str, result, &pos, &i))
			return (free_split(result), NULL);
	}
	result[i] = NULL;
	return (result);
}
