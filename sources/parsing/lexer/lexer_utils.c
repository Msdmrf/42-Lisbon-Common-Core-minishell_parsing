/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 22:18:02 by migusant          #+#    #+#             */
/*   Updated: 2026/02/06 00:46:26 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

int	count_backslashes(char *str, int i)
{
	int	count;
	int	check;

	count = 0;
	check = i - 1;
	while (check >= 0 && str[check] == '\\')
	{
		count++;
		check--;
	}
	return (count);
}

static int	is_escaped_quote(char *input, int i, char quote)
{
	int	backslash_count;

	if (quote != '"')
		return (0);
	backslash_count = count_backslashes(input, i);
	return (backslash_count % 2 == 1);
}

static int	calculate_quoted_length(char *input, int *i, char quote)
{
	int	len;

	len = 1;
	(*i)++;
	while (input[*i])
	{
		if (input[*i] == quote)
		{
			if (is_escaped_quote(input, *i, quote))
			{
				len++;
				(*i)++;
				continue ;
			}
			break ;
		}
		len++;
		(*i)++;
	}
	if (input[*i] == quote)
	{
		len++;
		(*i)++;
	}
	return (len);
}

static int	calculate_word_length(char *input, int start)
{
	int	len;
	int	i;

	len = 0;
	i = start;
	while (input[i] && !is_whitespace(input[i])
		&& !is_special_char(input[i]))
	{
		if (input[i] == '\'' || input[i] == '"')
			len += calculate_quoted_length(input, &i, input[i]);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*handle_word(char *input, int *i)
{
	char	*word;
	int		len;
	int		j;

	len = calculate_word_length(input, *i);
	if (len == 0)
		return (NULL);
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	j = 0;
	while (input[*i] && !is_whitespace(input[*i])
		&& !is_special_char(input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '"')
			copy_quoted_section(word, input, &j, i);
		else
			word[j++] = input[(*i)++];
	}
	word[j] = '\0';
	return (word);
}
