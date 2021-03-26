/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:14:49 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/26 14:55:11 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_list **env_head, t_list **cmd_head, t_cmd *com, char *user)
{ //TODO: id con comillas: espacios no válidos (e.g. "hola que"=algo)
	t_list	*new;
	t_list	*list;
	t_env	*env;
	int		i;
	int		len_id;
	int		len_v;
	int		flag;
	int		r;

	r = 0;
	if (com->args == NULL)
	{
		list = *env_head;
		while (list)
		{
			if (((t_env*)list->content)->value)
				printf("declare -x %s=\"%s\"\n", ((t_env*)list->content)->id, ((t_env*)list->content)->value);
			else
				printf("declare -x %s\n", ((t_env*)list->content)->id);
			list = list->next;
		}
		return (r);
	}
	i = 0;
	while (i < com->n_args)
	{
		flag = 0;
		len_id = 0;
		len_v = 0;
		if (!ft_isalpha(com->args[i][0]))
		{
			write(1, "Error: not an identifier\n", 25);
			i++;
			r = 1;
			continue ;
		}
		if (!ft_strchr(com->args[i], '='))
		{
			list = *env_head;
			while (list)
			{
				if (!ft_strcmp(((t_env*)list->content)->id, com->args[i]))
				{
					flag = 1;
					break;
				}
				list = list->next;
			}
			if (!flag)
			{
				new = malloc(sizeof(t_list));
				if (!new)
					ft_exit(env_head, cmd_head, user);
				env = malloc(sizeof(t_env));
				if (!new)
					ft_exit(env_head, cmd_head, user);
				new->content = env;
				((t_env*)new->content)->id = ft_strdup(com->args[i]);
				if (!((t_env*)new->content)->id)
					ft_exit(env_head, cmd_head, user);
				((t_env*)new->content)->value = NULL;
				ft_lstadd_back(env_head, new);
			}
			i++;
			continue ;
		}
		while (com->args[i][len_id] != '=')
			len_id++;
		len_v = ft_strlen(&com->args[i][len_id + 1]);
		list = *env_head;
		while (list)
		{
			if (!ft_strncmp(((t_env*)list->content)->id, com->args[i], len_id))
			{
				free(((t_env *)list->content)->value);
				((t_env *)list->content)->value = ft_substr(com->args[i], len_id + 1, len_v);
				flag = 1;
				break;
			}
			list = list->next;
		}
		if (!flag)
		{
			new = malloc(sizeof(t_list));
			if (!new)
				ft_exit(env_head, cmd_head, user);
			env = malloc(sizeof(t_env));
			if (!env)
				ft_exit(env_head, cmd_head, user);
			new->content = env;
			((t_env *)new->content)->id = ft_substr(com->args[i], 0, len_id);
			if (!((t_env *)new->content)->id)
				ft_exit(env_head, cmd_head, user);
			((t_env *)new->content)->value = ft_substr(com->args[i], len_id + 1, len_v);
			if (!((t_env *)new->content)->value)
				ft_exit(env_head, cmd_head, user);
			ft_lstadd_back(env_head, new);
		}
		i++;
	}
	return (r);
}
