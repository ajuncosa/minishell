/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 11:47:54 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/04/02 16:48:33 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_data data, t_cmd *com)
{
	t_list	*prev;
	t_list	*list;
	int		i;

	i = 0;
	while (i < com->n_args)
	{
		list = data.env_head;
		while (list)
		{
			if (!ft_strcmp(((t_env*)list->content)->id, com->args[i]))
			{
				if (list == data.env_head)
				{
					data.env_head = list->next;
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
