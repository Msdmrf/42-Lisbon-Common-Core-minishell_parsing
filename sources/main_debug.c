/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 19:18:38 by migusant          #+#    #+#             */
/*   Updated: 2026/02/15 22:40:35 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static char	*token_type_str(t_token_type type)
{
	if (type == TOKEN_WORD)
		return ("WORD");
	else if (type == TOKEN_PIPE)
		return ("PIPE");
	else if (type == TOKEN_SEMICOLON)
		return ("SEMICOLON");
	else if (type == TOKEN_REDIR_IN)
		return ("REDIR_IN");
	else if (type == TOKEN_REDIR_OUT)
		return ("REDIR_OUT");
	else if (type == TOKEN_REDIR_APPEND)
		return ("REDIR_APPEND");
	else if (type == TOKEN_REDIR_HEREDOC)
		return ("REDIR_HEREDOC");
	return ("UNKNOWN");
}

void	print_tokens(t_token *tokens, char *stage)
{
	int	i;
	int	show_wd_split;

	i = 0;
	show_wd_split = (ft_strncmp(stage, "TOKENS (after expansion)", 24) == 0);
	printf("\n%s:\n", stage);
	while (tokens)
	{
		printf("[%d] Type: %-15s Value: %s",
			i, token_type_str(tokens->type), tokens->value);
		if (tokens->type == TOKEN_WORD && show_wd_split)
			printf(" (wd_split: %d)", tokens->wd_split);
		printf("\n");
		tokens = tokens->next;
		i++;
	}
}

static void	print_redirections(t_redir *redir)
{
	while (redir)
	{
		printf("        Redir: %s %s",
			token_type_str(redir->type), redir->file);
		if (redir->type == TOKEN_REDIR_HEREDOC)
			printf(" (hd_expand: %d)", redir->hd_expand);
		printf("\n");
		redir = redir->next;
	}
}

void	print_cmd_list(t_cmd *cmd_list, char *stage)
{
	int	cmd_num;
	int	i;

	cmd_num = 0;
	printf("\n%s:\n", stage);
	while (cmd_list)
	{
		printf("[%d] Args:\n", cmd_num);
		i = 0;
		while (cmd_list->args && cmd_list->args[i])
		{
			printf("    [%d] = %s\n", i, cmd_list->args[i]);
			i++;
		}
		if (cmd_list->redirections)
			print_redirections(cmd_list->redirections);
		cmd_list = cmd_list->next;
		cmd_num++;
	}
	printf("\n");
}
