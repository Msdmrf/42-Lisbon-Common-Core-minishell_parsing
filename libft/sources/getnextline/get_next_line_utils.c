/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:48:00 by migusant          #+#    #+#             */
/*   Updated: 2025/05/27 12:59:34 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

char	*gnl_ft_strlenchr(const char *s, size_t *len)
{
	size_t	i;

	i = 0;
	if (!s)
	{
		if (len)
			*len = 0;
		return (NULL);
	}
	while (s[i] && s[i] != '\n')
		i++;
	if (len)
		*len = i + (s[i] == '\n');
	if (s[i] != '\n')
		return (NULL);
	return ((char *)s + i);
}

char	*gnl_ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	lens[2];
	size_t	idx[2];

	gnl_ft_strlenchr(s1, &lens[0]);
	gnl_ft_strlenchr(s2, &lens[1]);
	str = malloc(lens[0] + lens[1] + 1);
	if (!str)
		return (free(s1), NULL);
	idx[0] = 0;
	idx[1] = 0;
	while (s1 && s1[idx[0]])
		str[idx[1]++] = s1[idx[0]++];
	idx[0] = 0;
	while (s2[idx[0]])
	{
		str[idx[1]++] = s2[idx[0]];
		if (s2[idx[0]++] == '\n')
			break ;
	}
	str[idx[1]] = '\0';
	return (free(s1), str);
}

void	gnl_ft_buffer_clean(char *buffer)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		buffer[i++] = '\0';
	if (buffer[i] == '\n')
		buffer[i++] = '\0';
	j = 0;
	while (buffer[i])
	{
		buffer[j++] = buffer[i];
		buffer[i++] = '\0';
	}
}
