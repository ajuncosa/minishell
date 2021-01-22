/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 11:47:54 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/01/22 14:13:23 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_list *head, char *str)
{
	t_list	*prev;
	t_list	*list;
	t_list	*tmp;
	char	**items;
	int		cont;
	int		del;
	int		i;
	int		j;
	int		k;

	cont = 0;
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\n' || str[i] == '\0')
	{
		write(1, "unset: not enough arguments\n", 28);
		return ;
	}
	k = i;
	while (str[k] != '\n' && str[k] != '\0')
	{
		while (str[k] != ' ' && str[k] != '\n' && str[k] != '\0')
			k++;
		while (str[k] == ' ')
			k++;
		cont++;
	}
	items = ft_split(&str[i], ' ');																// FIXME: el último item se guarda con '\n' incluido
	list = head;
	while (list)																				// TODO: comparar cada item con todos los envs
	{
		j = 0;
		del = 0;
		tmp = list;
	printf("%s\n", ((t_env*)head->content)->id);

		while (j < cont)
		{
			if (!ft_strncmp(((t_env*)list->content)->id, items[j], ft_strlen(items[j]) - 1 ))	// FIXME: el -1 del strlen es por lo del \n del item, sólo funciona si le pasas sólo un item
																								// FIXME: hay que comparar con el len del más largo, si hay varios id que empiezan por TERM y unseteas TERM se te borran todos
			{
				if (list == head)																// FIXME: este caso da segmentation fault
				{
					printf("entro 1\n");
					head = list->next;
					ft_lstdelone(list, &del_lst);
				}
				else
				{
					printf("entro 2\n");
					prev->next = list->next;
					ft_lstdelone(list, &del_lst);
				}
				del = 1;
				break ;
			}
			j++;
		}
		if (!del)
			prev = list;
		list = tmp->next;
	}
}
