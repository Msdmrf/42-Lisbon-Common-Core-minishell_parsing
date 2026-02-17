/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 09:54:55 by migusant          #+#    #+#             */
/*   Updated: 2026/02/17 14:24:23 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

char	*dup_char_and_advance(char c, int *i)
{
	char	char_str[2];

	char_str[0] = c;
	char_str[1] = '\0';
	(*i)++;
	return (ft_strdup(char_str));
}

static char	*get_env_value(char *var_name)
{
	char	*value;

	if (!var_name || !var_name[0])
		return (ft_strdup(""));
	else if (ft_strncmp(var_name, "?", 2) == 0)
		return (ft_itoa(shell()->exit_code));
	else if (ft_strlen(var_name) == 1 && !ft_isalnum(var_name[0])
		&& var_name[0] != '_')
		return (ft_strdup(""));
	value = ft_getenv(shell()->envp, var_name);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

char	*expand_var_from_name(char *var_name)
{
	char	*var_value;

	if (!var_name || !var_name[0])
	{
		free(var_name);
		return (ft_strdup("$"));
	}
	var_value = get_env_value(var_name);
	free(var_name);
	return (var_value);
}

char	*append_string(char *result, char *to_add)
{
	char	*temp;

	temp = ft_strjoin(result, to_add);
	free(to_add);
	if (!temp)
	{
		free(result);
		return (NULL);
	}
	free(result);
	return (temp);
}

char	*append_char(char *result, char c)
{
	char	char_str[2];
	char	*temp;

	char_str[0] = c;
	char_str[1] = '\0';
	temp = ft_strjoin(result, char_str);
	if (!temp)
	{
		free(result);
		return (NULL);
	}
	free(result);
	return (temp);
}
