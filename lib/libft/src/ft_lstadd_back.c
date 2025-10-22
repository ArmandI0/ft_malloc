/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:32:54 by aranger           #+#    #+#             */
/*   Updated: 2023/11/06 11:32:55 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	struct s_list	*a;

	if (lst && new)
	{
		a = ft_lstlast(*lst);
		if (a != 0)
			a->next = new;
		else
			*lst = new;
	}
}
