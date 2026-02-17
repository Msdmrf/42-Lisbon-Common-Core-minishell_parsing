/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 11:36:05 by migusant          #+#    #+#             */
/*   Updated: 2026/02/17 14:23:53 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static char	*process_heredoc_char(char *str, int *i)
{
	if (str[*i] == '\\' && str[*i + 1])
	{
		if (str[*i + 1] == '$' || str[*i + 1] == '`' || str[*i + 1] == '\\')
		{
			(*i)++;
			return (dup_char_and_advance(str[*i], i));
		}
		return (dup_char_and_advance(str[*i], i));
	}
	else if (str[*i] == '$')
	{
		if (str[*i + 1])
			return (expand_var_from_name(extract_var_name(str, i)));
		else
			return (dup_char_and_advance('$', i));
	}
	else
		return (dup_char_and_advance(str[*i], i));
}

char	*expand_heredoc_line(char *line)
{
	char	*result;
	char	*segment;
	int		i;

	if (!line)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (line[i])
	{
		segment = process_heredoc_char(line, &i);
		if (!segment)
			return (free(result), NULL);
		result = append_string(result, segment);
		if (!result)
			return (NULL);
	}
	return (result);
}
