/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 22:19:20 by migusant          #+#    #+#             */
/*   Updated: 2026/02/06 00:48:07 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static int	count_args(char **args)
{
	int	count;

	count = 0;
	if (!args)
		return (0);
	while (args[count])
		count++;
	return (count);
}

static char	**allocate_new_args(char **old_args, char *new_arg, int count)
{
	char	**new_args;
	int		i;

	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_args[i] = old_args[i];
		i++;
	}
	new_args[i] = new_arg;
	new_args[i + 1] = NULL;
	return (new_args);
}

static void	add_arg_to_cmd(t_cmd *cmd, char *arg)
{
	char	**new_args;
	char	*arg_copy;
	int		count;

	if (!arg)
		return ;
	count = count_args(cmd->args);
	arg_copy = ft_strdup(arg);
	if (!arg_copy)
		return ;
	new_args = allocate_new_args(cmd->args, arg_copy, count);
	if (!new_args)
	{
		free(arg_copy);
		return ;
	}
	free(cmd->args);
	cmd->args = new_args;
}

static void	add_redir_to_cmd(t_cmd *cmd, t_token_type type, char *file,
	int hd_expand)
{
	t_redir	*new_redir;
	t_redir	*current;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->file = ft_strdup(file);
	if (!new_redir->file)
	{
		free(new_redir);
		return ;
	}
	new_redir->type = type;
	new_redir->fd = -1;
	new_redir->hd_expand = hd_expand;
	new_redir->next = NULL;
	if (!cmd->redirections)
		cmd->redirections = new_redir;
	else
	{
		current = cmd->redirections;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
}

t_token	*parse_cmd(t_cmd *cmd, t_token *current)
{
	int	hd_expand;

	while (current && current->type != TOKEN_PIPE
		&& current->type != TOKEN_SEMICOLON)
	{
		if (current->type == TOKEN_WORD)
		{
			add_arg_to_cmd(cmd, current->value);
			current = current->next;
		}
		else if (current->type >= TOKEN_REDIR_IN
			&& current->type <= TOKEN_REDIR_HEREDOC)
		{
			if (!current->next || current->next->type != TOKEN_WORD)
				return (NULL);
			hd_expand = current->next->hd_expand;
			add_redir_to_cmd(cmd, current->type, current->next->value,
				hd_expand);
			current = current->next->next;
		}
		else
			current = current->next;
	}
	return (current);
}
