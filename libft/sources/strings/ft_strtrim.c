/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:43:51 by migusant          #+#    #+#             */
/*   Updated: 2025/05/26 17:25:44 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*s3;

	if (!s1)
		return (NULL);
	if (!set && s1)
		return (ft_strdup(s1));
	start = 0;
	while (s1[start] && ft_strchr(set, (int)s1[start]))
		start++;
	if (s1[start] == '\0')
		return (ft_strdup(""));
	end = ft_strlen(s1) - 1;
	while (end >= start && ft_strchr(set, (int)s1[end]))
		end--;
	s3 = malloc(sizeof(char) * ((end - start + 1) + 1));
	if (!s3)
		return (NULL);
	ft_strlcpy(s3, &s1[start], ((end - start + 1) + 1));
	return (s3);
}
