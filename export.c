/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:14:49 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/08 13:52:14 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_list **head, t_cmd *com)	//TODO: returns para $?
											//TODO: comillas? export "args[0]" = hola => bad assignment && te mete args[0] en env
{
	t_list	*new;
	t_list	*list;
	t_env	*env;
	int		i;
	int		len_id;
	int		len_v;

	if (com->args == NULL)
	{
		list = *head;
		while (list)
		{
			write(1, ((t_env*)list->content)->id, ft_strlen(((t_env*)list->content)->id));
			write(1, "=", 1);
			write(1, ((t_env*)list->content)->value, ft_strlen(((t_env*)list->content)->value));
			write(1, "\n", 1);
			list = list->next;
		}
		return (0);
	}
	i = 0;
	while (i < com->n_args)
	{
		len_id = 0;
		len_v = 0;
		if (!ft_isalpha(com->args[i][0]))
		{
			write(1, "Error: not an identifier\n", 25);
			return (1);
		}
		if (!ft_strchr(com->args[i], '='))
		{
			write(1, "bad assignment\n", 15);
			return (0);
		}
		while (com->args[i][len_id] != '=')
			len_id++;
		new = malloc(sizeof(t_list));
		env = malloc(sizeof(t_env));
		new->content = env;
		((t_env *)new->content)->id = ft_substr(com->args[i], 0, len_id);
		len_v = ft_strlen(&com->args[i][len_id + 1]);
		list = *head;
		while (list)
		{
			if (!ft_strncmp(((t_env*)list->content)->id, ((t_env *)new->content)->id, len_id))
			{
				free(((t_env *)list->content)->value);
				free(((t_env *)new->content)->id);
				break;
			}
			list = list->next;
		}
		((t_env *)new->content)->value = ft_substr(com->args[i], len_id + 1, len_v);
		ft_lstadd_back(head, new);
		i++;
	}
	return (0);
}
