/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 19:18:36 by migusant          #+#    #+#             */
/*   Updated: 2026/02/15 22:39:48 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static int	tokenize_and_validate(char *input)
{
	shell()->toks = lexer(input);
	if (!shell()->toks)
		return (0);
	if (!check_syntax())
	{
		free_tokens(shell()->toks);
		shell()->toks = NULL;
		return (0);
	}
	return (1);
}

void	process(char *input)
{
	if (!tokenize_and_validate(input))
		return ;
	if (!parser())
	{
		free_tokens(shell()->toks);
		shell()->toks = NULL;
		free_cmd_list(shell()->cmds);
		shell()->cmds = NULL;
		return ;
	}
	if (MINISHELL_DEBUG)
		print_cmd_list(shell()->cmds, "COMMANDS");
	free_tokens(shell()->toks);
	shell()->toks = NULL;
	free_cmd_list(shell()->cmds);
	shell()->cmds = NULL;
}
