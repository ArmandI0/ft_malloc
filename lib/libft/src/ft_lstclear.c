/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:28:15 by aranger           #+#    #+#             */
/*   Updated: 2023/11/06 12:28:18 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	struct s_list	*tmp;
	struct s_list	*tmp1;

	if (lst && (del))
	{
		tmp = *lst;
		while (tmp)
		{
			tmp1 = tmp->next;
			ft_lstdelone(tmp, del);
			tmp = tmp1;
		}
		*lst = NULL;
	}
}
