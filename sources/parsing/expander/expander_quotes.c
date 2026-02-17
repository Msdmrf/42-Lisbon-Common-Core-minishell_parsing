/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 09:54:52 by migusant          #+#    #+#             */
/*   Updated: 2026/01/30 09:30:00 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

char	*expand_single_quotes(char *str, int *i)
{
	int	start;

	start = *i;
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (str[*i] == '\'')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

static char	*handle_expansion_char(char *str, int *i, char **result)
{
	char	*expansion;

	if (str[*i] == '\\' && str[*i + 1] && (str[*i + 1] == '$'
			|| str[*i + 1] == '\\'))
	{
		*result = append_char(*result, str[*i + 1]);
		(*i) += 2;
	}
	else if (str[*i] == '$')
	{
		expansion = expand_variable(str, i);
		*result = append_string(*result, expansion);
	}
	else
	{
		*result = append_char(*result, str[*i]);
		(*i)++;
	}
	return (*result);
}

static int	handle_escaped_quote(char *str, int *i, char **result)
{
	if (str[*i] == '\\' && str[*i + 1] == '"')
	{
		*result = append_char(*result, '\\');
		if (!*result)
			return (0);
		*result = append_char(*result, '"');
		if (!*result)
			return (0);
		(*i) += 2;
		return (1);
	}
	return (0);
}

char	*expand_double_quotes(char *str, int *i)
{
	char	*result;

	(*i)++;
	result = ft_strdup("\"");
	if (!result)
		return (NULL);
	while (str[*i] && str[*i] != '"')
	{
		if (handle_escaped_quote(str, i, &result))
			continue ;
		if (!handle_expansion_char(str, i, &result))
			return (NULL);
	}
	if (str[*i] == '"')
	{
		result = append_char(result, '"');
		if (!result)
			return (NULL);
		(*i)++;
	}
	return (result);
}

char	*expand_ansi_c_quotes(char *str, int *i)
{
	int	start;

	(*i)++;
	start = *i;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (str[*i] == '\'')
		(*i)++;
	return (ft_substr(str, start, *i - start - 1));
}
