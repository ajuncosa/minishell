/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 11:47:54 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/03/08 18:55:14 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_list **head, t_cmd *com)
{
	t_list	*prev;
	t_list	*list;
	int		i;
	int		len;
	int		lenv;

	i = 0;
	if (com->args == NULL)
	{
		write(1, "unset: not enough arguments\n", 28);
		return (1);
	}
	while (i < com->n_args)
	{
		list = *head;
		len = (i == com->n_args - 1) ? ft_strlen(com->args[i]) - 1 : ft_strlen(com->args[i]);
		while (list)
		{
			lenv = ft_strlen(((t_env*)list->content)->id);
			lenv = (lenv < len) ? len : lenv;
			if (!ft_strncmp(((t_env*)list->content)->id, com->args[i], lenv))
			{
				if (list == *head)
				{
					*head = list->next;
					ft_lstdelone(list, &del_lst);
				}
				else
				{
					prev->next = list->next;
					ft_lstdelone(list, &del_lst);
				}
				break ;
			}
			prev = list;
			list = list->next;
		}
		i++;
	}
	return (0);
}
