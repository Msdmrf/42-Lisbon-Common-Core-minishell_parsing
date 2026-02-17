/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 09:57:13 by migusant          #+#    #+#             */
/*   Updated: 2026/02/06 00:51:31 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static int	skip_quotes(char *str, int *i, char quote_char)
{
	int	len;

	(*i)++;
	len = 0;
	while (str[*i] && str[*i] != quote_char)
	{
		len++;
		(*i)++;
	}
	if (str[*i] == quote_char)
		(*i)++;
	return (len);
}

int	count_unquoted_len(char *str)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			len += skip_quotes(str, &i, '\'');
		else if (str[i] == '"')
			len += skip_quotes(str, &i, '"');
		else if (str[i] == '\\' && (str[i + 1] == '"' || str[i + 1] == '\''))
		{
			len++;
			i += 2;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

void	copy_unquoted(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] == '\'')
			copy_single_quoted(dest, src, &j, &i);
		else if (src[i] == '"')
			copy_double_quoted(dest, src, &j, &i);
		else if (src[i] == '\\' && (src[i + 1] == '"' || src[i + 1] == '\''))
		{
			dest[j++] = src[i + 1];
			i += 2;
		}
		else
			dest[j++] = src[i++];
	}
	dest[j] = '\0';
}
