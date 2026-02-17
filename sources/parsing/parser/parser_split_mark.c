/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split_mark.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 09:13:25 by migusant          #+#    #+#             */
/*   Updated: 2026/02/06 00:48:20 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static int	is_variable_assignment(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (str[i] == '=' && i > 0);
}

static int	is_escaped_quote_at(char *str, int i)
{
	int	backslash_count;

	if (i == 0 || str[i - 1] != '\\')
		return (0);
	backslash_count = count_backslashes(str, i);
	return (backslash_count % 2 == 1);
}

static int	handle_quote_char(char *str, int *i, int *in_quote,
	char *quote_type)
{
	if (!*in_quote && (str[*i] == '"' || str[*i] == '\''))
	{
		*in_quote = 1;
		*quote_type = str[*i];
	}
	else if (*in_quote && str[*i] == *quote_type)
	{
		if (*quote_type == '"' && is_escaped_quote_at(str, *i))
		{
			(*i)++;
			return (1);
		}
		*in_quote = 0;
		*quote_type = 0;
	}
	return (0);
}

static int	has_unquoted_whitespace(char *str)
{
	int		i;
	int		in_quote;
	char	quote_type;

	i = 0;
	in_quote = 0;
	quote_type = 0;
	while (str[i])
	{
		if (handle_quote_char(str, &i, &in_quote, &quote_type))
			continue ;
		if (!in_quote && (str[i] == ' ' || str[i] == '\t'))
			return (1);
		i++;
	}
	return (0);
}

void	mark_word_split(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD
			&& !is_variable_assignment(tokens->value)
			&& has_unquoted_whitespace(tokens->value))
			tokens->wd_split = 1;
		else
			tokens->wd_split = 0;
		tokens = tokens->next;
	}
}
