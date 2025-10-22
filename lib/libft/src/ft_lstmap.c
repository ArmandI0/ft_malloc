/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:10:04 by aranger           #+#    #+#             */
/*   Updated: 2023/11/06 14:10:06 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	struct s_list	*startlst;
	struct s_list	*newlist;
	struct s_list	**oldlist;

	if (lst && (f) && (del))
	{
		oldlist = &lst;
		newlist = ft_lstnew(f(lst->content));
		startlst = newlist;
		lst = lst->next;
		while (lst)
		{
			newlist->next = ft_lstnew(f(lst->content));
			newlist = newlist->next;
			lst = lst->next;
		}
		ft_lstclear(oldlist, del);
		return (startlst);
	}
	return (NULL);
}
