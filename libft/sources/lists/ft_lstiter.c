/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:19:33 by migusant          #+#    #+#             */
/*   Updated: 2025/05/26 17:22:41 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*temp_node;

	if (!lst || !f)
		return ;
	temp_node = lst;
	while (temp_node)
	{
		f(temp_node->content);
		temp_node = temp_node->next;
	}
}
