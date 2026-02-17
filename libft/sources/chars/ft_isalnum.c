/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:18:15 by migusant          #+#    #+#             */
/*   Updated: 2025/05/26 17:18:07 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_isalnum(int c)
{
	if (c == EOF || (c >= 0 && c <= 255))
	{
		if (ft_isalpha(c) || ft_isdigit(c))
			return (1);
	}
	return (0);
}
