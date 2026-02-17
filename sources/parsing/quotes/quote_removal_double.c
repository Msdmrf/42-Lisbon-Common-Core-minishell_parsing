/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal_double.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 11:48:05 by migusant          #+#    #+#             */
/*   Updated: 2026/02/06 00:52:03 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static int	is_escaped_quote(char *src, int i)
{
	int	backslash_count;

	if (src[i] != '"')
		return (0);
	backslash_count = count_backslashes(src, i);
	return (backslash_count % 2 == 1);
}

static int	handle_escaped_backslash(char *src, int *i, char *dest, int *j)
{
	if (src[*i] == '\\' && src[*i + 1] == '\\')
	{
		dest[(*j)++] = '\\';
		(*i) += 2;
		return (1);
	}
	return (0);
}

static int	handle_escaped_quote_char(char *src, int *i, char *dest, int *j)
{
	if (src[*i] == '\\' && src[*i + 1] == '"')
	{
		dest[(*j)++] = '"';
		(*i) += 2;
		return (1);
	}
	return (0);
}

void	copy_double_quoted(char *dest, char *src, int *j, int *i)
{
	(*i)++;
	while (src[*i])
	{
		if (src[*i] == '"' && !is_escaped_quote(src, *i))
			break ;
		if (handle_escaped_quote_char(src, i, dest, j))
			continue ;
		if (handle_escaped_backslash(src, i, dest, j))
			continue ;
		dest[(*j)++] = src[(*i)++];
	}
	if (src[*i] == '"')
		(*i)++;
}
