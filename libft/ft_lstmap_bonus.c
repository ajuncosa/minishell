/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 10:05:51 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/01/27 11:44:37 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*beginning;

	if (!lst || !f)
		return (NULL);
	if (!(beginning = ft_lstnew(f(lst->content))))
		return (NULL);
	new = beginning;
	while (lst->next)
	{
		lst = lst->next;
		if (!(new->next = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&beginning, del);
			return (NULL);
		}
		new = new->next;
	}
	new->next = NULL;
	return (beginning);
}
