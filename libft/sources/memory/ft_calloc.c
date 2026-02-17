/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:25:24 by migusant          #+#    #+#             */
/*   Updated: 2025/05/26 17:23:28 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*nmemb_mem;
	size_t	max_size;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	max_size = nmemb * size;
	if (size != 0 && nmemb != (max_size / size))
		return (NULL);
	nmemb_mem = malloc(nmemb * size);
	if (!nmemb_mem)
		return (NULL);
	ft_bzero(nmemb_mem, nmemb * size);
	return (nmemb_mem);
}
