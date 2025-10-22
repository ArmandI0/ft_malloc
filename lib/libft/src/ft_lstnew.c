/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 09:18:31 by aranger           #+#    #+#             */
/*   Updated: 2023/11/06 09:18:42 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	struct s_list	*a;

	a = malloc(sizeof(t_list));
	if (a == NULL)
		return (NULL);
	a->content = content;
	a->next = NULL;
	return (a);
}
