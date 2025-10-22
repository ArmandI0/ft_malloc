/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:37:26 by aranger           #+#    #+#             */
/*   Updated: 2023/11/06 12:37:31 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	struct s_list	*ptr;

	if (lst)
	{
		(*f)(lst->content);
		ptr = lst->next;
		while (ptr != NULL)
		{
			(*f)(ptr->content);
			ptr = ptr->next;
		}
	}
}
