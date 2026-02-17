/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 09:42:51 by migusant          #+#    #+#             */
/*   Updated: 2026/02/16 17:14:25 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static int	is_redir_token(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_HEREDOC);
}

static void	print_syntax_error(t_token *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (!token)
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd(token->value, 2);
	ft_putstr_fd("'\n", 2);
}

static int	check_redir_syntax(t_token *token)
{
	if (!token->next || token->next->type != TOKEN_WORD)
	{
		print_syntax_error(token->next);
		return (0);
	}
	return (1);
}

static int	check_pipe_syntax(t_token *token, t_token *prev)
{
	if (!prev)
	{
		print_syntax_error(token);
		return (0);
	}
	if (!token->next || token->next->type == TOKEN_PIPE)
	{
		print_syntax_error(token->next);
		return (0);
	}
	return (1);
}

int	check_syntax(void)
{
	t_token	*current;
	t_token	*prev;

	if (!shell() || !shell()->toks)
		return (0);
	current = shell()->toks;
	prev = NULL;
	while (current)
	{
		if (is_redir_token(current->type))
		{
			if (!check_redir_syntax(current))
				return (shell()->exit_code = 2, 0);
		}
		else if (current->type == TOKEN_PIPE)
		{
			if (!check_pipe_syntax(current, prev))
				return (shell()->exit_code = 2, 0);
		}
		prev = current;
		current = current->next;
	}
	return (1);
}
