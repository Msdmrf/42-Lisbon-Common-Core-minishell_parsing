/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 09:47:58 by migusant          #+#    #+#             */
/*   Updated: 2026/02/15 22:38:22 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

t_shell	*shell(void)
{
	static t_shell	data;

	return (&data);
}

static int	init_shell(char **envp)
{
	shell()->envp = envp;
	shell()->cmds = NULL;
	shell()->toks = NULL;
	shell()->exit_code = 0;
	setup_signals(SIG_INTERACTIVE);
	return (1);
}

static void	shell_loop(void)
{
	char	*input;
	int		validation_result;

	while (1)
	{
		input = readline("minishell$ ");
		validation_result = validate_input(input);
		if (validation_result == 1)
			break ;
		else if (validation_result == 2)
		{
			free(input);
			continue ;
		}
		if (!*input)
		{
			free(input);
			continue ;
		}
		add_history(input);
		process(input);
		free(input);
	}
}

void	cleanup_resources(int mode)
{
	if (MINISHELL_DEBUG)
	{
		if (mode == CLEANUP_CHILD)
			ft_printf("Cleaning up child...\n");
		else
			ft_printf("Cleaning up shell...\n");
	}
	if (mode == CLEANUP_PARENT)
		rl_clear_history();
	free_tokens(shell()->toks);
	shell()->toks = NULL;
	free_cmd_list(shell()->cmds);
	shell()->cmds = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	if (!init_shell(envp))
		return (1);
	shell_loop();
	cleanup_resources(CLEANUP_PARENT);
	return (shell()->exit_code);
}
