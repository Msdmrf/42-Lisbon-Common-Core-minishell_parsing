/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 22:18:38 by migusant          #+#    #+#             */
/*   Updated: 2026/02/15 22:41:38 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirections = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	add_cmd_to_list(t_cmd **head, t_cmd *new_cmd)
{
	t_cmd	*current;

	if (!*head)
	{
		*head = new_cmd;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_cmd;
}

static t_token	*build_cmd(t_cmd **cmd_list, t_token *current_token)
{
	t_cmd	*current_cmd;

	current_cmd = create_cmd();
	if (!current_cmd)
	{
		free_cmd_list(*cmd_list);
		return (NULL);
	}
	current_token = parse_cmd(current_cmd, current_token);
	if (!current_token && !current_cmd->args && !current_cmd->redirections)
	{
		free_cmd(current_cmd);
		return (NULL);
	}
	add_cmd_to_list(cmd_list, current_cmd);
	if (current_token && (current_token->type == TOKEN_PIPE
			|| current_token->type == TOKEN_SEMICOLON))
		current_token = current_token->next;
	return (current_token);
}

static void	remove_empty_word_tokens(void)
{
	t_token	*current;
	t_token	*prev;
	t_token	*temp;

	prev = NULL;
	current = shell()->toks;
	while (current)
	{
		if (current->type == TOKEN_WORD
			&& current->value && current->value[0] == '\0')
		{
			temp = current;
			if (prev)
				prev->next = current->next;
			else
				shell()->toks = current->next;
			current = current->next;
			free(temp->value);
			free(temp);
			continue ;
		}
		prev = current;
		current = current->next;
	}
}

int	parser(void)
{
	t_token	*current_token;

	if (MINISHELL_DEBUG)
		print_tokens(shell()->toks, "TOKENS (raw)");
	expand_tokens();
	remove_empty_word_tokens();
	if (!shell()->toks)
		return (shell()->cmds = NULL, 1);
	if (MINISHELL_DEBUG)
		print_tokens(shell()->toks, "TOKENS (after expansion)");
	mark_word_split(shell()->toks);
	apply_word_split(&shell()->toks);
	if (MINISHELL_DEBUG)
		print_tokens(shell()->toks, "TOKENS (after word splitting)");
	mark_heredoc_expansion(shell()->toks);
	handle_quotes();
	if (MINISHELL_DEBUG)
		print_tokens(shell()->toks, "TOKENS (after quote removal)");
	shell()->cmds = NULL;
	current_token = shell()->toks;
	while (current_token)
		current_token = build_cmd(&shell()->cmds, current_token);
	if (!shell()->cmds)
		return (0);
	return (1);
}
