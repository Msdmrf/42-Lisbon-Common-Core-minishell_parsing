/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_substitutions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 09:11:08 by migusant          #+#    #+#             */
/*   Updated: 2026/02/17 14:22:50 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

char	*expand_tilde(char *str, int *i)
{
	char	*home;

	if (*i == 0 && str[*i] == '~' && (!str[*i + 1] || str[*i + 1] == '/'))
	{
		home = ft_getenv(shell()->envp, "HOME");
		if (!home || !*home)
		{
			(*i)++;
			return (ft_strdup("~"));
		}
		(*i)++;
		return (ft_strdup(home));
	}
	(*i)++;
	return (ft_strdup("~"));
}

char	*extract_var_name(char *str, int *i)
{
	int	start;

	(*i)++;
	if (str[*i] == '?')
		return (dup_char_and_advance('?', i));
	if (ft_isdigit(str[*i]))
		return (dup_char_and_advance(str[*i], i));
	if (str[*i] && !ft_isalnum(str[*i]) && str[*i] != '_')
		return (dup_char_and_advance(str[*i], i));
	start = *i;
	if (str[*i] && (ft_isalpha(str[*i]) || str[*i] == '_'))
	{
		(*i)++;
		while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
			(*i)++;
	}
	return (ft_substr(str, start, *i - start));
}

static char	*handle_backslash_outside_quotes(char *str, int *i)
{
	char	*result;

	if (!str[*i + 1])
		return (dup_char_and_advance('\\', i));
	if (str[*i + 1] == '"' || str[*i + 1] == '\'')
	{
		result = malloc(3);
		if (!result)
			return (NULL);
		result[0] = '\\';
		result[1] = str[*i + 1];
		result[2] = '\0';
		(*i) += 2;
		return (result);
	}
	(*i)++;
	return (dup_char_and_advance(str[*i], i));
}

char	*expand_variable(char *str, int *i)
{
	if (str[*i] == '\\')
		return (handle_backslash_outside_quotes(str, i));
	else if (str[*i] == '$')
	{
		if (str[*i + 1] && (ft_isalnum(str[*i + 1])
				|| str[*i + 1] == '_' || str[*i + 1] == '?'))
			return (expand_var_from_name(extract_var_name(str, i)));
		else
			return (dup_char_and_advance('$', i));
	}
	else
		return (dup_char_and_advance(str[*i], i));
}
