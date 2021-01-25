/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 11:47:54 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/01/25 12:01:27 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_list *head, char *str)
{
	t_list	*prev;
	t_list	*list;
	char	**items;
	int		cont;
	int		i;
	int		j;
	int		len;
	int		lenv;

	cont = 0;
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\n' || str[i] == '\0')
	{
		write(1, "unset: not enough arguments\n", 28);
		return ;
	}
	j = i;
	while (str[j] != '\n' && str[j] != '\0')
	{
		while (str[j] != ' ' && str[j] != '\n' && str[j] != '\0')
			j++;
		while (str[j] == ' ')
			j++;
		cont++;
	}
	items = ft_split(&str[i], ' ');
	j = 0;
	while (j < cont)
	{
		list = head;
		len = (j == cont - 1) ? ft_strlen(items[j]) - 1 : ft_strlen(items[j]);
		while (list)
		{
			lenv = ft_strlen(((t_env*)list->content)->id);
			lenv = (lenv < len) ? len : lenv;
			if (!ft_strncmp(((t_env*)list->content)->id, items[j], lenv))
			{
				if (list == head)																// FIXME: este caso da segmentation fault
				{
					head = list->next;
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
		j++;
	}
}
