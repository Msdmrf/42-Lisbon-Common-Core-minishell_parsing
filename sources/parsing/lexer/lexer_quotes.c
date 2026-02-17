/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 10:39:29 by migusant          #+#    #+#             */
/*   Updated: 2026/02/06 00:46:43 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static int	should_close_quote(char *src, int i, char quote)
{
	int	backslash_count;

	if (src[i] != quote)
		return (0);
	if (quote != '"')
		return (1);
	backslash_count = count_backslashes(src, i);
	return (backslash_count % 2 == 0);
}

void	copy_quoted_section(char *dst, char *src, int *dst_pos, int *src_pos)
{
	char	quote;

	quote = src[*src_pos];
	dst[*dst_pos] = quote;
	(*src_pos)++;
	(*dst_pos)++;
	while (src[*src_pos])
	{
		if (should_close_quote(src, *src_pos, quote))
			break ;
		dst[*dst_pos] = src[*src_pos];
		(*src_pos)++;
		(*dst_pos)++;
	}
	if (src[*src_pos] == quote)
	{
		dst[*dst_pos] = quote;
		(*src_pos)++;
		(*dst_pos)++;
	}
}
