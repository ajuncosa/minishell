/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 11:47:54 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/04/08 13:57:19 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_errors(char *str)
{
	int i;

	i = 0;
	while (ft_isalpha(str[i]))
	{
		printf("unset: `%s': not a valid identifier\n", str);
		i++;
		return (0);
	}
	while (str[i] != '=' && str[i] != '\0')
	{
		if (str[i] == ' ')
		{
			printf("unset: `%s': not a valid identifier\n", str);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_unset(t_data data, t_cmd *com)
{
	t_list	*prev;
	t_list	*list;
	int		i;
	int		r;

	r = 0;
	i = 0;
	while (i < com->n_args)
	{
		if (!unset_errors(com->args[i]))
		{
			i++;
			r = 1;
			continue ;
		}
		list = data.env_head;
		printf("|%s|\n", com->args[i]);
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
