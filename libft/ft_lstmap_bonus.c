/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 10:05:51 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/05 13:49:06 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*beginning;

	if (!lst || !f)
		return (NULL);
	beginning = ft_lstnew(f(lst->content));
	if (!beginning)
		return (NULL);
	new = beginning;
	while (lst->next)
	{
		lst = lst->next;
		new->next = ft_lstnew(f(lst->content));
		if (!new->next)
		{
			ft_lstclear(&beginning, del);
			return (NULL);
		}
		new = new->next;
	}
	new->next = NULL;
	return (beginning);
}
