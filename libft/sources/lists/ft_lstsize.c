/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:17:17 by migusant          #+#    #+#             */
/*   Updated: 2025/05/26 17:23:13 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*temp_node;

	if (!lst)
		return (0);
	count = 0;
	temp_node = lst;
	while (temp_node)
	{
		temp_node = temp_node->next;
		count++;
	}
	return (count);
}
