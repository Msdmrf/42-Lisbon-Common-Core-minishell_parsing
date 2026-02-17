/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:56:03 by migusant          #+#    #+#             */
/*   Updated: 2025/05/26 18:30:48 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strdup(const char *s)
{
	char	*s_dest;

	if (!s)
		return (NULL);
	s_dest = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!s_dest)
		return (NULL);
	ft_strlcpy(s_dest, s, ft_strlen(s) + 1);
	return (s_dest);
}
