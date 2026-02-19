/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 09:09:57 by migusant          #+#    #+#             */
/*   Updated: 2026/02/19 18:55:33 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static char	*get_next_segment(char *token, int *i)
{
	if (*i == 0 && token[*i] == '~')
		return (expand_tilde(token, i));
	else if (token[*i] == '\'')
		return (expand_single_quotes(token, i));
	else if (token[*i] == '"')
		return (expand_double_quotes(token, i));
	else if (token[*i] == '$' && token[*i + 1] == '\'')
	{
		(*i)++;
		return (expand_ansi_c_quotes(token, i));
	}
	else if (token[*i] == '$' && token[*i + 1] == '"')
	{
		(*i)++;
		return (expand_double_quotes(token, i));
	}
	else
		return (expand_variable(token, i));
}

char	*expand_token(char *token)
{
	char	*result;
	char	*segment;
	int		i;

	if (!token)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (token[i])
	{
		segment = get_next_segment(token, &i);
		if (!segment)
			return (free(result), NULL);
		result = append_string(result, segment);
		if (!result)
			return (NULL);
	}
	return (result);
}

static void	try_expand_token(t_token *token)
{
	char	*expanded;

	expanded = expand_token(token->value);
	if (expanded)
	{
		free(token->value);
		token->value = expanded;
	}
}

static int	should_expand_redir(t_token *token)
{
	return (token->type >= TOKEN_REDIR_IN
		&& token->type <= TOKEN_REDIR_APPEND
		&& token->next
		&& token->next->type == TOKEN_WORD);
}

void	expand_tokens(void)
{
	t_token	*tokens;

	tokens = shell()->toks;
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
			try_expand_token(tokens);
		else if (tokens->type == TOKEN_REDIR_HEREDOC)
		{
			tokens = tokens->next;
			if (tokens && tokens->type == TOKEN_WORD)
				tokens = tokens->next;
			continue ;
		}
		else if (should_expand_redir(tokens))
			try_expand_token(tokens->next);
		tokens = tokens->next;
	}
	remove_empty_word_tokens();
}
