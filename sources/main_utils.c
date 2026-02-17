/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 19:18:33 by migusant          #+#    #+#             */
/*   Updated: 2026/02/06 00:43:07 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static int	skip_double_quoted(char *str, int *i)
{
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == '\\' && str[*i + 1] && (str[*i + 1] == '"'
				|| str[*i + 1] == '\\' || str[*i + 1] == '$'))
		{
			(*i) += 2;
			continue ;
		}
		if (str[*i] == '"')
		{
			(*i)++;
			return (1);
		}
		(*i)++;
	}
	return (0);
}

static int	skip_single_quoted(char *str, int *i)
{
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (str[*i] == '\'')
	{
		(*i)++;
		return (1);
	}
	return (0);
}

static char	get_unclosed_quote_type(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1])
		{
			i += 2;
			continue ;
		}
		if (str[i] == '\'')
		{
			if (!skip_single_quoted(str, &i))
				return ('\'');
		}
		else if (str[i] == '"')
		{
			if (!skip_double_quoted(str, &i))
				return ('"');
		}
		else
			i++;
	}
	return (0);
}

static void	print_unclosed_quote_error(char quote)
{
	ft_putstr_fd("minishell: unexpected EOF while ", 2);
	ft_putstr_fd("looking for matching `", 2);
	ft_putchar_fd(quote, 2);
	ft_putstr_fd("'\n", 2);
}

int	validate_input(char *input)
{
	char	unclosed_quote;

	if (!input)
	{
		printf("exit\n");
		return (1);
	}
	unclosed_quote = get_unclosed_quote_type(input);
	if (unclosed_quote)
	{
		print_unclosed_quote_error(unclosed_quote);
		return (2);
	}
	return (0);
}
