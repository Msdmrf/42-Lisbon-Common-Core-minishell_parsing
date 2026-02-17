/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 09:12:44 by migusant          #+#    #+#             */
/*   Updated: 2026/02/16 23:03:46 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static char	*remove_quotes(char *str)
{
	char	*result;
	int		len;

	if (!str)
		return (NULL);
	len = count_unquoted_len(str);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	copy_unquoted(result, str);
	return (result);
}

static void	try_remove_quotes(t_token *token)
{
	char	*unquoted;

	unquoted = remove_quotes(token->value);
	if (unquoted)
	{
		free(token->value);
		token->value = unquoted;
	}
}

void	handle_quotes(void)
{
	t_token	*tokens;

	tokens = shell()->toks;
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
			try_remove_quotes(tokens);
		else if (tokens->type >= TOKEN_REDIR_IN
			&& tokens->type <= TOKEN_REDIR_APPEND
			&& tokens->next
			&& tokens->next->type == TOKEN_WORD)
		{
			try_remove_quotes(tokens->next);
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
}
