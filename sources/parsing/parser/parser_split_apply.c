/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split_apply.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 10:13:38 by migusant          #+#    #+#             */
/*   Updated: 2026/02/16 23:03:08 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static int	replace_first_word(t_token *current, char *new_value)
{
	char	*first_word;

	first_word = ft_strdup(new_value);
	if (!first_word)
		return (0);
	free(current->value);
	current->value = first_word;
	current->wd_split = 0;
	return (1);
}

static void	insert_remaining_words(t_token *prev, char **words)
{
	t_token	*new_token;
	char	*word_copy;
	int		i;

	i = 1;
	while (words[i])
	{
		word_copy = ft_strdup(words[i]);
		if (word_copy)
		{
			new_token = create_token(TOKEN_WORD, word_copy);
			if (new_token)
			{
				new_token->next = prev->next;
				prev->next = new_token;
				prev = new_token;
			}
		}
		i++;
	}
}

static void	insert_split_tokens(t_token *current, char **words)
{
	if (!words || !words[0])
		return ;
	if (!replace_first_word(current, words[0]))
		return ;
	insert_remaining_words(current, words);
}

static void	normalize_ifs(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\t' || str[i] == '\n')
			str[i] = ' ';
		i++;
	}
}

void	apply_word_split(t_token **tokens)
{
	t_token	*current;
	t_token	*next;
	char	**words;

	current = *tokens;
	while (current)
	{
		next = current->next;
		if (current->type == TOKEN_WORD && current->wd_split == 1)
		{
			normalize_ifs(current->value);
			words = ft_split(current->value, ' ');
			if (words)
			{
				insert_split_tokens(current, words);
				free_split(words);
			}
		}
		current = next;
	}
}
