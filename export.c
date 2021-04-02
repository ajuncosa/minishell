/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:14:49 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/04/02 16:44:34 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_errors(char *str)
{
	int i;

	i = 0;
	if (!ft_isalpha(str[0]))
	{
		write(1, "Error: not a valid identifier\n", 31);
		return (0);
	}
	while (str[i] != '=' && str[i] != '\0')
	{
		if (str[i] == ' ')
		{
			write(1, "Error: not a valid identifier\n", 31);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_export(t_data data, t_cmd *com)
{
	t_list	*new;
	t_list	*list;
	t_env	*env;
	int		i;
	int		j;
	int		len_id;
	int		len_v;
	int		flag;
	int		r;

	r = 0;
	if (com->args == NULL)
	{
		list = data.env_head;
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

		if (!export_errors(com->args[i]))
		{
			i++;
			r = 1;
			continue ;
		}
		if (!ft_strchr(com->args[i], '='))
		{
			list = data.env_head;
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
					ft_exit(data);
				env = malloc(sizeof(t_env));
				if (!new)
					ft_exit(data);
				new->content = env;
				((t_env*)new->content)->id = ft_strdup(com->args[i]);
				if (!((t_env*)new->content)->id)
					ft_exit(data);
				((t_env*)new->content)->value = NULL;
				ft_lstadd_back(&data.env_head, new);
			}
			i++;
			continue ;
		}
		while (com->args[i][len_id] != '=')
			len_id++;
		len_v = ft_strlen(&com->args[i][len_id + 1]);
		list = data.env_head;
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
				ft_exit(data);
			env = malloc(sizeof(t_env));
			if (!env)
				ft_exit(data);
			new->content = env;
			((t_env *)new->content)->id = ft_substr(com->args[i], 0, len_id);
			if (!((t_env *)new->content)->id)
				ft_exit(data);
			((t_env *)new->content)->value = ft_substr(com->args[i], len_id + 1, len_v);
			if (!((t_env *)new->content)->value)
				ft_exit(data);
			ft_lstadd_back(&data.env_head, new);
		}
		i++;
	}
	return (r);
}
