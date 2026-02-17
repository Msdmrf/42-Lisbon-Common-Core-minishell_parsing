/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:26:16 by migusant          #+#    #+#             */
/*   Updated: 2025/05/26 18:16:37 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*temp_s;

	if (!s)
		return (NULL);
	temp_s = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (temp_s[i] == (unsigned char)c)
			return ((void *)&temp_s[i]);
		i++;
	}
	return (NULL);
}
